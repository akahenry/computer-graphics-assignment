#include "engine.hpp"
#include "window.hpp"
#include "GLFW/linmath.h"

int main()
{
    Engine eng;

    eng.Initialize();

    Window window = Window(800, 600, "teeste");
}