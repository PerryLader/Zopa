#include "global.h"

int maxFPS = 120;
std::stack<Action> ActionStack;
Mode mode = Mode::Idle;
bool ctrlPressed = false;
float* controledColums = nullptr;
float* controledRows = nullptr;
float* controledSize = nullptr;
glm::vec2* controledPos = nullptr;
glm::vec2* controledDir = nullptr;
float DeleteButtonSize= 0.0125f;


