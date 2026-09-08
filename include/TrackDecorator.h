#ifndef TRACKDECORATOR_H
#define TRACKDECORATOR_H

#include "WorkComponent.h"

// ---- Decorator (GoF) ---------------------------------------------------
// TrackDecorator is the Decorator participant: it IS-A WorkComponent and
// HAS-A WorkComponent, so any number of decorators can wrap a Track (or
// wrap each other) and the result is still usable anywhere a plain
// WorkComponent is expected — added to a session, iterated over, asked
// its cost/duration/stage.
class TrackDecorator : public WorkComponent {
public:
    explicit TrackDecorator(WorkComponent* wrapped) : wrapped_(wrapped) {}

    // Owns the wrapped component — deleting a decorator chain deletes the
    // whole chain down to the real Track (Rule 4 & 5).
    ~TrackDecorator() override { delete wrapped_; }

    // Default pass-through behaviour. Concrete decorators override only
    // what they actually change, so stacking composes cleanly.
    std::string getName() const override { return wrapped_->getName(); }
    double getTotalDuration() const override { return wrapped_->getTotalDuration(); }
    double getTotalCost() const override { return wrapped_->getTotalCost(); }
    std::string getStageName() const override { return wrapped_->getStageName(); }

    // Forwarded so a decorated Track is fully transparent to Composite and
    // Iterator — without these, a decorated track would silently look like
    // an empty, stage-less leaf to FullCatalogIterator/PendingStageIterator.
    std::vector<WorkComponent*> getChildrenForIteration() const override {
        return wrapped_->getChildrenForIteration();
    }
    bool matchesStage(Stage target) const override { return wrapped_->matchesStage(target); }

protected:
    WorkComponent* wrapped_;
};

// ---- Concrete decorators ------------------------------------------------

// Adds a compliance/label-review cost and tags the name.
class ExplicitContentDecorator : public TrackDecorator {
public:
    explicit ExplicitContentDecorator(WorkComponent* wrapped) : TrackDecorator(wrapped) {}
    std::string getName() const override { return wrapped_->getName() + " [Explicit]"; }
    double getTotalCost() const override { return wrapped_->getTotalCost() + 75.0; }
};

// Expedites the work: pay more, take less time.
class RushOrderDecorator : public TrackDecorator {
public:
    explicit RushOrderDecorator(WorkComponent* wrapped) : TrackDecorator(wrapped) {}
    std::string getName() const override { return wrapped_->getName() + " (Rush)"; }
    double getTotalCost() const override { return wrapped_->getTotalCost() * 1.5; }
    double getTotalDuration() const override { return wrapped_->getTotalDuration() * 0.5; }
};

// Adds a guest artist: licensing cost, name credit.
class FeaturedArtistDecorator : public TrackDecorator {
public:
    FeaturedArtistDecorator(WorkComponent* wrapped, const std::string& featuredArtist)
        : TrackDecorator(wrapped), featuredArtist_(featuredArtist) {}
    std::string getName() const override {
        return wrapped_->getName() + " (feat. " + featuredArtist_ + ")";
    }
    double getTotalCost() const override { return wrapped_->getTotalCost() + 300.0; }
private:
    std::string featuredArtist_;
};

// Adds a remix pass: extra production cost and time.
class RemixDecorator : public TrackDecorator {
public:
    explicit RemixDecorator(WorkComponent* wrapped) : TrackDecorator(wrapped) {}
    std::string getName() const override { return wrapped_->getName() + " (Remix)"; }
    double getTotalCost() const override { return wrapped_->getTotalCost() + 200.0; }
    double getTotalDuration() const override { return wrapped_->getTotalDuration() + 4.0; }
};

#endif
