#include <FinEngine.h>
#include "States/TestState.h"

int main() {
    FinEngine::FinGame game(new TestState());
}