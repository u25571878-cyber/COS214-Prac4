#ifndef ITERATOR_H
#define ITERATOR_H

class WorkComponent; //forward declaration

//Iterator (GoF)
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual WorkComponent* next() = 0; // caller must check hasNext() first
};

#endif
