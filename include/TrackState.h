#ifndef TRACKSTATE_H
#define TRACKSTATE_H

#include <string>
#include "Stage.h" // Stage enum now lives here so WorkComponent.h can use it too

class Track; // forward declaration — states operate on a Track by reference

// State (GoF)
class TrackState {
public:
    virtual ~TrackState() = default;

    virtual Stage getStage() const = 0;
    virtual std::string getStageName() const = 0;

    //different per state, not just a different printed label.
    virtual double getCost(const Track& track) const = 0;
    virtual double getEstimatedCompletionTime(const Track& track) const = 0;
    virtual TrackState* getNextState() const = 0;
};

//Concrete states
class DemoState : public TrackState {
public:
    Stage getStage() const override { return Stage::DEMO; }
    std::string getStageName() const override { return "Demo"; }
    double getCost(const Track& track) const override;
    double getEstimatedCompletionTime(const Track& track) const override;
    TrackState* getNextState() const override;
};

class RecordingState : public TrackState {
public:
    Stage getStage() const override { return Stage::RECORDING; }
    std::string getStageName() const override { return "Recording"; }
    double getCost(const Track& track) const override;
    double getEstimatedCompletionTime(const Track& track) const override;
    TrackState* getNextState() const override;
};

class MixingState : public TrackState {
public:
    Stage getStage() const override { return Stage::MIXING; }
    std::string getStageName() const override { return "Mixing"; }
    double getCost(const Track& track) const override;
    double getEstimatedCompletionTime(const Track& track) const override;
    TrackState* getNextState() const override;
};

class MasteringState : public TrackState {
public:
    Stage getStage() const override { return Stage::MASTERING; }
    std::string getStageName() const override { return "Mastering"; }
    double getCost(const Track& track) const override;
    double getEstimatedCompletionTime(const Track& track) const override;
    TrackState* getNextState() const override;
};

class ReleasedState : public TrackState {
public:
    Stage getStage() const override { return Stage::RELEASED; }
    std::string getStageName() const override { return "Released"; }
    double getCost(const Track& track) const override;
    double getEstimatedCompletionTime(const Track& track) const override;
    TrackState* getNextState() const override; // returns nullptr — terminal
};

#endif
