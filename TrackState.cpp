#include "TrackState.h"
#include "Track.h"

// DemoState
double DemoState::getCost(const Track& track) const {
    return track.getBaseCost() * 0.10; // cheap — just a scratch take
}
double DemoState::getEstimatedCompletionTime(const Track& track) const {
    return track.getBaseHours() * 0.20;
}
TrackState* DemoState::getNextState() const {
    return new RecordingState();
}

//RecordingState
double RecordingState::getCost(const Track& track) const {
    return track.getBaseCost() * 0.50; // studio day-rate kicks in
}
double RecordingState::getEstimatedCompletionTime(const Track& track) const {
    return track.getBaseHours() * 0.60; // the most time-intensive stage
}
TrackState* RecordingState::getNextState() const {
    return new MixingState();
}

//mixingState
double MixingState::getCost(const Track& track) const {
    return track.getBaseCost() * 0.75;
}
double MixingState::getEstimatedCompletionTime(const Track& track) const {
    return track.getBaseHours() * 0.30;
}
TrackState* MixingState::getNextState() const {
    return new MasteringState();
}

//MasteringState
double MasteringState::getCost(const Track& track) const {
    return track.getBaseCost() * 0.90;
}
double MasteringState::getEstimatedCompletionTime(const Track& track) const {
    return track.getBaseHours() * 0.15; // fast, specialised pass
}
TrackState* MasteringState::getNextState() const {
    return new ReleasedState();
}

//ReleasedState (terminal)
double ReleasedState::getCost(const Track& track) const {
    return track.getBaseCost(); // full realise
}
double ReleasedState::getEstimatedCompletionTime(const Track& /*track*/) const {
    return 0.0; 
}
TrackState* ReleasedState::getNextState() const {
    return nullptr; // in the terminal Track::advance()/attemptTransitionTo() must handle this
}
