#ifndef TRACK_H
#define TRACK_H

#include "WorkComponent.h"
#include <string>

/**
 * Track - GoF "Leaf" role in the Composite pattern.
 *
 * NOTE FOR PERSON B: this is intentionally a skeleton. You will add:
 *   - a TrackState* currentState member
 *   - delegate getTotalDuration()/getTotalCost() to currentState
 *   - lifecycle transition methods (advance(), etc.)
 * Please don't change the constructor signature without telling A + C,
 * since RecordingSession and main.cpp scenarios both construct Tracks directly.
 */
class Track : public WorkComponent {
private:
    std::string name;
    // TrackState* currentState;  <-- Person B adds this

public:
    Track(const std::string& trackName) : name(trackName) {}

    std::string getName() const override { return name; }

    // STUBS - Person B replaces these with state-delegated behaviour.
    double getTotalDuration() const override { return 0.0; }
    double getTotalCost() const override { return 0.0; }

    // Track has no children, so it uses WorkComponent's default
    // getChildrenForIteration() (returns empty) and createIterator()
    // (returns nullptr) without needing to override either.

    ~Track() override {}
};

#endif