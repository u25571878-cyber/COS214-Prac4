#ifndef FULLCATALOGITERATOR_H
#define FULLCATALOGITERATOR_H

#include "Iterator.h"
#include "WorkComponent.h"
#include <vector>
#include <stack>

// Depth-first full traversal of the hierarchy.
// Snapshot policy: the iterator captures the structure at construction time
// so later structural changes do not affect an in-progress traversal.
class FullCatalogIterator : public Iterator {
private:
    std::vector<WorkComponent*> snapshot;  // flattened depth-first order
    size_t currentIndex;

    void buildSnapshot(WorkComponent* root);

public:
    explicit FullCatalogIterator(WorkComponent* root);
    virtual ~FullCatalogIterator() {}

    void first() override;
    void next() override;
    bool isDone() const override;
    WorkComponent* currentItem() const override;
};

#endif
