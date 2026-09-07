#ifndef TRACK_H
#define TRACK_H

#include <string>
#include "WorkComponent.h"
#include "TrackState.h"

// Leaf (Composite) / Context (State)

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
    std::string title_;
    double baseCost_;
    double baseHours_;
    TrackState* currentState_; // owned

public:
    Track(const std::string& title) : title_(title), baseCost_(0), baseHours_(0), currentState_(new DemoState()) {}
    Track(const std::string& title, double baseCost, double baseHours);
    ~Track() override; // must delete currentState_ (Rule 4 & 5)

    std::string getName() const override;
    double getTotalCost() const override;       //currentState_->getCost(*this)
    double getTotalDuration() const override;    //currentState_->getEstimatedCompletionTime(*this)
    std::string getStageName() const override;

    
    double getBaseCost() const { return baseCost_; }
    double getBaseHours() const { return baseHours_; }

    bool advance();
    bool attemptTransitionTo(Stage target);

    Stage getStage() const { return currentState_->getStage(); }
    bool matchesStage(Stage target) const override { return getStage() == target; }


    // Track has no children, so it uses WorkComponent's default
    // getChildrenForIteration() (returns empty) and createIterator()
    // (returns nullptr) without needing to override either.
};

#endif