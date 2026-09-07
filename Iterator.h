#ifndef ITERATOR_H
#define ITERATOR_H

#include "WorkComponent.h"

// Abstract Iterator (Iterator pattern)
class Iterator {
public:
    virtual ~Iterator() {}

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual WorkComponent* currentItem() const = 0;
};

#endif
