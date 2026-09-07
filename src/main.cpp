#include "WorkComponent.h"
#include "Track.h"
#include "RecordingSession.h"
#include "ArtistProject.h"
#include "RecordLabel.h"
#include <iostream>

int main() {
    RecordLabel* label = new RecordLabel("Meridian Records");
    ArtistProject* project = new ArtistProject("Artist X Album");
    RecordingSession* session = new RecordingSession("Session 1");

    session->addChild(new Track("Track A"));
    session->addChild(new Track("Track B"));
    project->addChild(session);
    label->addChild(project);

    std::cout << label->getName() << " total cost: "
              << label->getTotalCost() << std::endl;

    delete label;
    return 0;
}