#include "WorkComponent.h"
#include "RecordLabel.h"
#include "ArtistProject.h"
#include "RecordingSession.h"
#include "Track.h"
#include "FullCatalogIterator.h"
#include "PendingStageIterator.h"
#include "Stage.h"
#include "TrackDecorator.h"

#include <iostream>
using namespace std;

// Small helper so the demo stays readable
void printItem(WorkComponent* c) {
    cout << "  - " << c->getName()
         << " | cost=" << c->getTotalCost()
         << " | duration=" << c->getTotalDuration()
         << " | stage=" << c->getStageName()
         << "\n";
}

void runIterator(Iterator* it, const string& title) {
    cout << "\n=== " << title << " ===\n";
    int count = 0;
    for (it->first(); !it->isDone(); it->next()) {
        printItem(it->currentItem());
        ++count;
    }
    cout << "  (" << count << " items)\n";
}

int main() {
    cout << "===== Meridian Records – TaskForge Demo =====\n";

    // 1. Build a 3-level hierarchy (Composite) RecordLabel → ArtistProject → RecordingSession → Track
    RecordLabel*   label   = new RecordLabel("Meridian Records");
    ArtistProject* project = new ArtistProject("Nova Echo – Debut");
    RecordingSession* session1 = new RecordingSession("Studio A");
    RecordingSession* session2 = new RecordingSession("Studio B");

    Track* t1 = new Track("Midnight Pulse", 1200.0, 10.0);
    Track* t2 = new Track("Echo Chamber",   1500.0, 12.0);
    Track* t3 = new Track("Silent Orbit",    900.0,  8.0);
    Track* t4 = new Track("Solar Flare",    1400.0, 11.0);

    //added missing decorator
    WorkComponent* t4Decorated =
        new RushOrderDecorator(
            new ExplicitContentDecorator(t4));

    session1->addChild(t1);
    session1->addChild(t2);
    session2->addChild(t3);
    session2->addChild(t4Decorated);

    project->addChild(session1);
    project->addChild(session2);
    label->addChild(project);

    cout << "\nHierarchy built.\n";
    cout << "Label total cost: " << label->getTotalCost() << "\n";
    cout << "Decorated track: " << t4Decorated->getName()
         << " | cost=" << t4Decorated->getTotalCost()
         << " (Decorator: RushOrder + ExplicitContent stacked on Solar Flare)\n";

    // 2. Full catalogue traversal (Iterator)
    Iterator* fullIt = label->createIterator();   // FullCatalogIterator
    runIterator(fullIt, "Full Catalogue (all items)");

    // 3. Advance some tracks (State)
    cout << "\n--- Advancing lifecycle ---\n";
    t1->advance();              // Demo -> Recording
    t1->advance();              // Recording -> Mixing
    t2->advance();              // Demo -> Recording
    t2->advance();              // Recording -> Mixing
    t2->advance();              // Mixing -> Mastering
    t3->advance();              // Demo -> Recording
    // t4 stays in Demo

    // Invalid transition demo
    cout << "\n--- Invalid transition demo ---\n";
    t2->attemptTransitionTo(Stage::DEMO);   // should be rejected

    // 4. Selective iterator – only Mixing tracks
    Iterator* mixingIt = new PendingStageIterator(label, "Mixing");
    runIterator(mixingIt, "Pending Mixing stage");

    Iterator* masteringIt = new PendingStageIterator(label, "Mastering");
    runIterator(masteringIt, "Pending Mastering stage");

    // 5. Snapshot policy proof (runtime structural change)
    cout << "\n--- Snapshot policy demo ---\n";
    Iterator* beforeIt = label->createIterator();   // snapshot taken NOW

    // Structural change AFTER the iterator was created
    Track* lateTrack = new Track("Afterglow", 1600.0, 9.0);
    session2->addChild(lateTrack);
    lateTrack->advance();
    lateTrack->advance();
    lateTrack->advance();
    lateTrack->advance();   // all the way to Released

    cout << "Added 'Afterglow' and advanced it to Released.\n";

    // New iterator sees the new track
    Iterator* afterIt = label->createIterator();
    runIterator(afterIt, "Full Catalogue AFTER add");

    // Old iterator does NOT see the new track (snapshot)
    runIterator(beforeIt, "Pre-change snapshot (should NOT contain Afterglow)");

    // 6. Final Released query
    Iterator* releasedIt = new PendingStageIterator(label, "Released");
    runIterator(releasedIt, "All Released tracks");

    // Cleanup
    delete fullIt;
    delete mixingIt;
    delete masteringIt;
    delete beforeIt;
    delete afterIt;
    delete releasedIt;
    delete label;   // deletes the whole tree

    cout << "\n=== Demo complete ===\n";
    return 0;
}
