#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H

#include <string>
#include <vector>
#include "Stage.h"

class WorkComponent {
public:
    virtual ~WorkComponent() = default;

    virtual std::string getName() const = 0;
    virtual double getTotalDuration() const = 0;
    virtual double getTotalCost() const = 0;
    virtual std::string getStageName() const { return ""; }

    virtual std::vector<WorkComponent*> getChildren() const { return {}; }
    virtual bool matchesStage(Stage /*target*/) const { return false; }
};

#endif
