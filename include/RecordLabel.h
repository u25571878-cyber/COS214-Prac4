#ifndef RECORDLABEL_H
#define RECORDLABEL_H

#include "WorkComponent.h"
#include <string>
#include <vector>

/**
 * RecordLabel - GoF "Composite" role, root of the hierarchy.
 * Holds ArtistProjects (as WorkComponent*).
 *
 * RecordLabel -> ArtistProject -> RecordingSession -> Track satisfies
 * Rule 6 (at least 3 levels of nesting below the root).
 *
 * Ownership policy matches the rest of the hierarchy: owns and deletes
 * children. Deleting a RecordLabel cascades through the entire tree.
 */
class RecordLabel : public WorkComponent {
private:
    std::string name;
    std::vector<WorkComponent*> children; // PRIVATE - Rule 7

public:
    RecordLabel(const std::string& labelName) : name(labelName) {}

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

    std::vector<WorkComponent*> getChildrenForIteration() const override {
        return children;
    }

    Iterator* createIterator() override {
        return nullptr; // Person C wires this up
    }

    ~RecordLabel() override {
        for (auto* c : children) {
            delete c;
        }
    }
};

#endif
