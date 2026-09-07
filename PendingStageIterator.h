#ifndef PENDINGSTAGEITERATOR_H
#define PENDINGSTAGEITERATOR_H

#include "Iterator.h"
#include "WorkComponent.h"
#include "Track.h"
#include "Stage.h"

#include <vector>
#include <string>

using namespace std;
// Selective iterator: only visits Tracks that are currently in a given lifecycle state.
class PendingStageIterator : public Iterator {
private:
    vector<WorkComponent*> matching;
    size_t currentIndex;
    string targetState;

    void collectMatching(WorkComponent* node);

public:
    PendingStageIterator(WorkComponent* root, const string& targetStateName);
    virtual ~PendingStageIterator() {}

    void first() override;
    void next() override;
    bool isDone() const override;
    WorkComponent* currentItem() const override;
};

#endif
