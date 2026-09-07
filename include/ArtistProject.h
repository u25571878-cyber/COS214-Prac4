#ifndef ARTISTPROJECT_H
#define ARTISTPROJECT_H

#include "WorkComponent.h"
#include "FullCatalogIterator.h"
#include <string>
#include <vector>

/**
 * ArtistProject - GoF "Composite" role, middle level of the hierarchy.
 * Holds RecordingSessions (as WorkComponent*), aggregating over them
 * the same way RecordingSession aggregates over Tracks.
 *
 * Ownership policy matches RecordingSession: owns and deletes children.
 */
class ArtistProject : public WorkComponent {
private:
    std::string name;
    std::vector<WorkComponent*> children; // PRIVATE - Rule 7

public:
    ArtistProject(const std::string& projectName) : name(projectName) {}

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
        return new FullCatalogIterator(this);
    }

    ~ArtistProject() override {
        for (auto* c : children) {
            delete c;
        }
    }
};

#endif