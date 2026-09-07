#include "PendingStageIterator.h"
#include "TrackDecorator.h"
#include "Track.h"

// Recursively collect only Tracks (or decorated Tracks) whose current state matches
void PendingStageIterator::collectMatching(WorkComponent* node) {
    if (!node) return;

    // Unwrap decorators to reach the real Track if present
    WorkComponent* current = node;
    while (true) {
        TrackDecorator* dec = dynamic_cast<TrackDecorator*>(current);
        if (dec) {
            current = dec->getWrapped();
        } else {
            break;
        }
    }

    Track* track = dynamic_cast<Track*>(current);
    if (track) {
        if (track->getStateName() == targetState) {
            matching.push_back(node);  // keep the (possibly decorated) object
        }
    }

    // Recurse using Person A's helper
    std::vector<WorkComponent*> children = node->getChildrenForIteration();
    for (WorkComponent* child : children) {
        collectMatching(child);
    }

   /* // Continue into children
    size_t n = node->getChildCount();
    for (size_t i = 0; i < n; ++i) {
        collectMatching(node->getChild(i));
    }*/
}

PendingStageIterator::PendingStageIterator(WorkComponent* root, const std::string& targetStateName) : currentIndex(0), targetState(targetStateName) {
    collectMatching(root);
}

void PendingStageIterator::first() {
    currentIndex = 0;
}

void PendingStageIterator::next() {
    if (!isDone()) {
        ++currentIndex;
    }
}

bool PendingStageIterator::isDone() const {
    return currentIndex >= matching.size();
}

WorkComponent* PendingStageIterator::currentItem() const {
    if (isDone()) return nullptr;
    return matching[currentIndex];
}
