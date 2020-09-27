#include <iostream>

// Definimos o callback para impressão de erros da GLFW no terminal
void ErrorCallback(int error, const char* description)
{
    std::cout << "ERROR: GLFW: " << description << std::endl;
}