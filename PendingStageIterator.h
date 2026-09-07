#ifndef PENDINGSTAGEITERATOR_H
#define PENDINGSTAGEITERATOR_H

#include <vector>
#include <cstddef>
#include "Iterator.h"
#include "WorkComponent.h"
#include "Stage.h"

//Concrete Iterator
class PendingStageIterator : public Iterator {
public:
    PendingStageIterator(WorkComponent* root, Stage target);

    bool hasNext() const override;
    WorkComponent* next() override;

private:
    void gather(WorkComponent* node, Stage target);

    std::vector<WorkComponent*> matches_;
    std::size_t index_;
};

#endif
