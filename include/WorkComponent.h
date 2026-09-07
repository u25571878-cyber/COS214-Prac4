#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H

#include <string>
#include <vector>
#include "Stage.h"

// Forward declaration - avoids circular include with Iterator.h.
// Person C will build the full Iterator hierarchy; we only need a pointer here.
class Iterator;

/**
 * WorkComponent - GoF "Component" role in the Composite pattern.
 *
 * Declares the uniform interface shared by both leaves (Track) and
 * composites (RecordLabel, ArtistProject, RecordingSession), so client
 * code (main.cpp) can treat a single item and an entire nested group
 * identically - this is the whole point of Composite.
 *
 * Also declares the createIterator() hook required by the Iterator
 * pattern (Rule 7: client code may never obtain the internal container
 * directly in order to traverse it).
 */
class WorkComponent {
public:
    virtual std::string getName() const = 0;
    virtual double getTotalDuration() const = 0;
    virtual double getTotalCost() const = 0;

    // Factory method (GoF) - concrete aggregates return a concrete iterator.
    // Default returns nullptr so leaves don't need to override it.
    virtual Iterator* createIterator() { return nullptr; }

    // Internal traversal helper used ONLY by Iterator implementations.
    // Returns a COPY of child pointers - this does NOT violate Rule 7,
    // since main.cpp never calls this directly; only Iterator subclasses do,
    // and they still only expose hasNext()/next() to the client.
    virtual std::vector<WorkComponent*> getChildrenForIteration() const {
        return {};
    }

    virtual ~WorkComponent() {} // Rule 4: every polymorphic base needs a virtual destructor

    // Person B's WorkComponent.h
    virtual std::string getStageName() const { return ""; }
    virtual bool matchesStage(Stage /*target*/) const { return false; }

};

#endif