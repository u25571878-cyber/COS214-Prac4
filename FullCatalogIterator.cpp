#include "FullCatalogIterator.h"
#include "CompositeGroups.h"
#include "TrackDecorator.h"

// Recursive depth-first collection into the snapshot vector
void FullCatalogIterator::buildSnapshot(WorkComponent* node) {
    if (!node) return;

    snapshot.push_back(node);

    // If it is a composite, continue into children
    size_t n = node->getChildCount();
    for (size_t i = 0; i < n; ++i) {
        buildSnapshot(node->getChild(i));
    }
}

FullCatalogIterator::FullCatalogIterator(WorkComponent* root)
    : currentIndex(0) {
    buildSnapshot(root);
}

void FullCatalogIterator::first() {
    currentIndex = 0;
}

void FullCatalogIterator::next() {
    if (!isDone()) {
        ++currentIndex;
    }
}

bool FullCatalogIterator::isDone() const {
    return currentIndex >= snapshot.size();
}

WorkComponent* FullCatalogIterator::currentItem() const {
    if (isDone()) return nullptr;
    return snapshot[currentIndex];
}
