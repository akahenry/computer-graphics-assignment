#include "engine.hpp"
#include "window.hpp"
#include "GLFW/linmath.h"

int main()
{
    Engine engine;

    engine.Initialize();

    Window window = Window(800, 600, "test");

    while (!window.ShouldClose())
    {
		window.ClearWindow(1.0f, 1.0f, 1.0f, 1.0f);
		window.DrawText("Texto de teste", 0, 0);
        window.PollEvents();
    }

    // Fim do programa
    return 0;
}