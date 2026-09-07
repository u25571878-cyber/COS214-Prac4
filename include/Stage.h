#ifndef STAGE_H
#define STAGE_H

#include <string>

// Pulled out of TrackState.h into its own header so WorkComponent.h can use
// it (for the Iterator hook below) without pulling in the whole State
// pattern. Purely a label + printable name — never used for switch-based
// behaviour, only for identification/logging and equality comparison.
enum class Stage {
    DEMO,
    RECORDING,
    MIXING,
    MASTERING,
    RELEASED
};

std::string stageToString(Stage stage);

#endif
