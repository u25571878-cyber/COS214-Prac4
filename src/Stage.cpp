#include "Stage.h"

std::string stageToString(Stage stage) {
    switch (stage) {
        case Stage::DEMO:      return "Demo";
        case Stage::RECORDING: return "Recording";
        case Stage::MIXING:    return "Mixing";
        case Stage::MASTERING: return "Mastering";
        case Stage::RELEASED:  return "Released";
    }
    return "Unknown";
}
