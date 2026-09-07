#include "Track.h"
#include <iostream>

Track::Track(const std::string& title, double baseCost, double baseHours)
    : title_(title), baseCost_(baseCost), baseHours_(baseHours),
      currentState_(new DemoState()) {}

Track::~Track() {
    delete currentState_;
}

std::string Track::getName() const {
    return title_;
}

double Track::getTotalCost() const {
    return currentState_->getCost(*this);
}

double Track::getTotalDuration() const {
    return currentState_->getEstimatedCompletionTime(*this);
}

std::string Track::getStageName() const {
    return currentState_->getStageName();
}

bool Track::advance() {
    TrackState* next = currentState_->getNextState();
    if (next == nullptr) {
        std::cout << "[" << title_ << "] cannot advance — already "
                  << currentState_->getStageName() << " (terminal stage).\n";
        return false;
    }
    std::cout << "[" << title_ << "] advancing: " << currentState_->getStageName()
              << " -> " << next->getStageName() << "\n";
    delete currentState_;
    currentState_ = next;
    return true;
}

bool Track::attemptTransitionTo(Stage target) {
    TrackState* proposed = currentState_->getNextState();

    if (proposed == nullptr) {
        std::cout << "[" << title_ << "] rejected transition to "
                  << stageToString(target) << " — track is already "
                  << currentState_->getStageName() << " and cannot move further.\n";
        return false;
    }

    if (proposed->getStage() != target) {
        std::cout << "[" << title_ << "] rejected transition to "
                  << stageToString(target) << " — from "
                  << currentState_->getStageName() << " the only legal next stage is "
                  << proposed->getStageName() << ".\n";
        delete proposed;
        return false;
    }

    std::cout << "[" << title_ << "] transitioning: " << currentState_->getStageName()
              << " -> " << proposed->getStageName() << "\n";
    delete currentState_;
    currentState_ = proposed;
    return true;
}
