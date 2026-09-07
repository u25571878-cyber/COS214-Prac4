#include "PendingStageIterator.h"
#include <stdexcept>
#include <iostream>

PendingStageIterator::PendingStageIterator(WorkComponent* root, Stage target)
    : index_(0) {
    if (root != nullptr) {
        gather(root, target);
    }
}

void PendingStageIterator::gather(WorkComponent* node, Stage target) {
    
    if (node->matchesStage(target)) {
        matches_.push_back(node);
    }
    for (WorkComponent* child : node->getChildren()) {
        gather(child, target);
    }
}

bool PendingStageIterator::hasNext() const {
    return index_ < matches_.size();
}

WorkComponent* PendingStageIterator::next() {
    if (!hasNext()) {
        std::cerr << "PendingStageIterator::next() called with nothing left "
                     "— check hasNext() first.\n";
        return nullptr;
    }
    return matches_[index_++];
}
