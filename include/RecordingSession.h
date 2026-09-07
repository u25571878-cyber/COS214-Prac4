#ifndef RECORDINGSESSION_H
#define RECORDINGSESSION_H

#include "WorkComponent.h"
#include "FullCatalogIterator.h"
#include <string>
#include <vector>

/**
 * RecordingSession - GoF "Composite" role (one of three levels).
 *
 * Holds children (Tracks, and possibly decorated Tracks) in a PRIVATE
 * container - Rule 7 forbids exposing this directly to main.cpp.
 * All access goes through the WorkComponent interface or through an
 * Iterator obtained via createIterator().
 *
 * Ownership policy: a RecordingSession OWNS its children. Destroying a
 * session recursively destroys everything nested inside it. This is a
 * deliberate design decision (see design doc rationale section) - it
 * keeps memory management simple and predictable: delete the root
 * RecordLabel, and the whole tree cleans itself up.
 */
class RecordingSession : public WorkComponent {
private:
    std::string name;
    std::vector<WorkComponent*> children; // PRIVATE - never exposed (Rule 7)

public:
    RecordingSession(const std::string& sessionName) : name(sessionName) {}

    void addChild(WorkComponent* child) {
        children.push_back(child);
    }

    std::string getName() const override { return name; }

    double getTotalDuration() const override {
        double total = 0.0;
        for (auto* c : children) {
            total += c->getTotalDuration();
        }
        return total;
    }

    double getTotalCost() const override {
        double total = 0.0;
        for (auto* c : children) {
            total += c->getTotalCost();
        }
        return total;
    }

    // Returns a COPY of the children pointers - used only by Iterator
    // implementations, never called directly from main.cpp.
    std::vector<WorkComponent*> getChildrenForIteration() const override {
        return children;
    }

    Iterator* createIterator() override {
        return new FullCatalogIterator(this);
    }

    ~RecordingSession() override {
        for (auto* c : children) {
            delete c; // owns children - Rule 4 & 5
        }
    }
};

#endif