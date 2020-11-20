#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <iostream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>

#include <error.hpp>
#include <shader.hpp>
#include <textrendering.hpp>
#include <engine.hpp>
#include <error.hpp>
#include <mesh.hpp>
#include <camera.hpp>
#include <color.hpp>
#include <input.hpp>
#include <scene.hpp>
#include <object.hpp>

#define CURSOR_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR_HIDDEN GLFW_CURSOR_HIDDEN
#define CURSOR_DISABLED GLFW_CURSOR_DISABLED

class Window
{
private:
    GLFWwindow* window;
    glm::vec2 size;
    GLuint program_id;
	Camera* currentCamera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	GLint model_uniform;
	GLint view_uniform;
	GLint projection_uniform;
	GLint render_as_black_uniform;
	GLint using_texture_uniform;
	GLint using_texture_coords_uniform;
	Shader defaultShader;
	double framerate = -1;
	double deltaTime = 0; // tempo desde o ultimo desenho da tela
	double lastTimeDrawn; // o tempo absoluto em que foi desenhado da ultima vez

	/**
	 * Set the function to be called when resizing the window
	 * 
	 * @param[in] callback a function to be called when resizing the window
	 */
    void SetFrameBufferSizeCallback(GLFWframebuffersizefun callback);

	/**
	 * Computes the view matrix based on the current camera and saves it in class attribute
	 */
	void CalcViewMatrix();
	
	/**
	 * Computes the projection matrix based on the current camera and saves it in class attribute
	 */
	void CalcProjectionMatrix();

	/**
	 * Computes the model matrix of an object to be projected in the scene based on rotation, translocation and scaling
	 * 
	 * @param[in] object an instance of GraphicObject to calculate the model matrix
	 */
	void CalcModelFromObject(GraphicObject obj);

	/**
	 * Draw the mesh with the texture on the window, sending it to GPU and calculating its color, projection
	 * on the camera near plane
	 * 
	 * @param[in] mesh an instance of Mesh to calculate the colors in GPU
	 * @param[in] usingTexture an bool representing if this mesh will use the texture when setting the colors in the shader
	 */
	void DrawMesh(Mesh mesh, bool usingTexture);

	/**
	 * Draw the mesh without a texture on the window, sending it to GPU and calculating its color, projection
	 * on the camera near plane
	 * 
	 * @param[in] mesh an instance of Mesh to calculate the colors in GPU
	 */
	void DrawMesh(Mesh mesh);

	/**
	 * Send all the data about the lights to shader in GPU
	 * 
	 * @param[in] scene an instance of Scene to get all the lights and send them to shader in GPU
	 */
	void SendLightsToShader(Scene& scene);
	
	/**
	 * Callback function to be used for every resize of the window
	 * 
	 * @param[in] window the resized window
	 * @param[in] width an integer representing the new width of the window
	 * @param[in] height an integer representing the new height of the window
	 */
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	
	/**
	 * Compute a 4x4 matrix using GLM
	 * 
	 * @param[in] m{ij} a float representing the number in the row i and in the column j
	 */
	static glm::mat4 MakeGlmMatrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	)
	{
		return glm::mat4(
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33
		);
	}

public:
	/**
	 * Compute an instance of Window class
	 * 
	 * @param[in] width an integer representing the width of the window
	 * @param[in] height an integer representing the height of the window
	 * @param[in] name a string representing the name of the window
	 * 
	 * @param[out] Window an instance of Window
	 */
	Window(int width, int height, const char* name);

	/**
	 * Compute the should close of the window if the user clicked to close the window
	 * 
	 * @param[out] should a bool representing if the window should close or not
	 */
    bool ShouldClose();

	/**
	 * Get the events from glfw and send it to Input class
	 */
    void PollEvents();

	/**
	 * Clear the window with the given color
	 * 
	 * @param[in] color an instance of Color class with the color to be used in all the screen
	 */
    void ClearWindow(Color color);

	/**
	 * Draw a text in the window
	 * 
	 * @param[in] str a string representing the text to be written on the screen
	 * @param[in] x a float representing the X component of the position
 	 * @param[in] y a float representing the y component of the position
 	 * @param[in] scale a float representing the scale of the text
	 */
	void DrawText(const std::string str, float x, float y, float scale = 1.0f);

	/**
	 * Draw a GraphicObject in the window, sending its component to shaders, calculating the model matrix
	 * and drawing the mesh based on this model matrix
	 * 
	 * @param[in] object an instance of GraphicObject
	 */
	void DrawObject(GraphicObject object);

	/**
	 * Set the camera to be used when projecting the scene in a plane
	 * 
	 * @param[in] camera an instance of Camera
	 */
	void SetCamera(Camera* camera);

	/**
	 * Compute the necessary stuff before drawing anything on the screen, including
	 * fill the screen with a color, calculating view and projection matrix and sending
	 * it to the shaders
	 * 
	 * @param[in] color an instance of Color class with the color to be used in all the screen
	 */
	void PreDrawing(Color clearColor);

	/**
	 * Compute the ratio between the width and the height of this screen
	 * 
	 * @param[in] ratio a float number representing the ratio between the width and the height of the window
	 */
	float GetScreenRatio();

	/**
	 * Set the type of the cursor
	 * 
	 * @param[in] type an integer representing the type of the cursor to be used
	 */
	void SetCursorType(int type);

	/**
	 * Draw a scene in the window, using its illumination and the objects, drawing
	 * them, sending to shaders
	 * 
	 * @param[in] scene an instance of Scene
	 */
	void DrawScene(Scene scene);

	/**
	 * Set a limit for frame rate
	 * 
	 * @param[in] framerate a double float representing the max framerate
	 */
	void SetFrameRateLimit(double framerate);

	/**
	 * Compute the time between the computation of the current frame and the last one
	 * 
	 * @param[out] time a double float representing the time in seconds between these two operations
	 */
	double GetDeltaTime(); // in seconds

	/**
	 * Compute the framerate based on the delta time calculated above
	 * 
	 * @param[out] time a double float representing the current framerate of this window
	 */
	double GetCurrentFramerate();
};
#endif