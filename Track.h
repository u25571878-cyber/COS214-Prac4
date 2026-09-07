#ifndef TRACK_H
#define TRACK_H

#include <string>
#include "WorkComponent.h"
#include "TrackState.h"

// Leaf (Composite) / Context (State)

class Track : public WorkComponent {
public:
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

private:
    std::string title_;
    double baseCost_;
    double baseHours_;
    TrackState* currentState_; // owned
};

#endif
