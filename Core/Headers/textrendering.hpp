#ifndef _TEXTRENDERING_HPP
#define _TEXTRENDERING_HPP

#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Declaração de funções auxiliares para renderizar texto dentro da janela
// OpenGL. Estas funções estão definidas no arquivo "textrendering.cpp".

 /**
 * Initialize the configuration to render text on the screen
 */
void TextRendering_Init();

 /**
 * Compute the line height based on the text scale and the window's height
 * 
 * @param[in] window a window to be used when calculates the height
 * 
 * @param[out] height a float representing the line height
 */
float TextRendering_LineHeight(GLFWwindow* window);

 /**
 * Compute the character width based on the text scale and the window's width
 * 
 * @param[in] window a window to be used when calculates the width
 * 
 * @param[out] width a float representing the character width
 */
float TextRendering_CharWidth(GLFWwindow* window);

 /**
 * Compute and shows the string at a specific position on the screen
 * 
 * @param[in] window a window to be used when calculates the width
 * @param[in] str a string to be written on the screen
 * @param[in] x a float representing the X component of the position
 * @param[in] y a float representing the y component of the position
 * @param[in] scale a float representing the scale of the text
 */
void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);

 /**
 * Compute and shows the matrix at a specific position on the screen
 * 
 * @param[in] window a window to be used when calculates the width
 * @param[in] matrix a 4x4 matrix to be written on the screen
 * @param[in] x a float representing the X component of the position
 * @param[in] y a float representing the y component of the position
 * @param[in] scale a float representing the scale of the text
 */
void TextRendering_PrintMatrix(GLFWwindow* window, glm::mat4 M, float x, float y, float scale = 1.0f);

 /**
 * Compute and shows the vector at a specific position on the screen
 * 
 * @param[in] window a window to be used when calculates the width
 * @param[in] vector a 4D vector to be written on the screen
 * @param[in] x a float representing the X component of the position
 * @param[in] y a float representing the y component of the position
 * @param[in] scale a float representing the scale of the text
 */
void TextRendering_PrintVector(GLFWwindow* window, glm::vec4 v, float x, float y, float scale = 1.0f);

 /**
 * Compute and shows the product between a matrix and a vector at a specific position on the screen
 * 
 * @param[in] window a window to be used when calculates the width
 * @param[in] matrix a 4x4 matrix to be written on the screen
 * @param[in] vector a 4D vector to be written on the screen
 * @param[in] x a float representing the X component of the position
 * @param[in] y a float representing the y component of the position
 * @param[in] scale a float representing the scale of the text
 */
void TextRendering_PrintMatrixVectorProduct(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

 /**
 * Compute and shows the product between a matrix and a vector at a specific position on the screen with more digits
 * 
 * @param[in] window a window to be used when calculates the width
 * @param[in] matrix a 4x4 matrix to be written on the screen
 * @param[in] vector a 4D vector to be written on the screen
 * @param[in] x a float representing the X component of the position
 * @param[in] y a float representing the y component of the position
 * @param[in] scale a float representing the scale of the text
 */
void TextRendering_PrintMatrixVectorProductMoreDigits(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

 /**
 * Compute and shows the product between a matrix and a vector at a specific position on the screen after W division
 * 
 * @param[in] window a window to be used when calculates the width
 * @param[in] matrix a 4x4 matrix to be written on the screen
 * @param[in] vector a 4D vector to be written on the screen
 * @param[in] x a float representing the X component of the position
 * @param[in] y a float representing the y component of the position
 * @param[in] scale a float representing the scale of the text
 */
void TextRendering_PrintMatrixVectorProductDivW(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

#endif