#pragma once
#pragma once

#include <vector.hpp>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include <iostream>

class Input
{
public:
	typedef struct
	{
		int button;
		bool pressed; // true == evento do tipo pressed, false == evento do tipo release
	} buttonEvent;

	class Mouse
	{
	public:
		// serve como buffer do callback, � usado no PollInputEvents pra atualizar as vari�veis relevantes s� uma vez por frame
		static Vector2 mousePositionFromCallback;

		static Vector2 mousePosition;
		static Vector2 mouseLastPosition;
		static Vector2 mousePositionDelta;

		/**
		 * Set the mousePositionFromCallback attribute with the mouse 2D components
		 * 
		 * @param[in] window the window which the event was released
		 * @param[in] xpos a double representing mouse X component
		 * @param[in] ypos a double representing mouse Y component
		 */
		static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		
		/**
		 * Push the event in a FIFO buffer
		 * 
		 * @param[in] window the window which the event was released
		 * @param[in] button an integer representing the button pressed/released
		 * @param[in] action an integer representing if the button was pressed or released
		 * @param[in] mods *deprecated*
		 */
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
	
	class Keyboard
	{
	public:
		/**
		 * Push the event in a FIFO buffer
		 * 
		 * @param[in] window the window which the event was released
		 * @param[in] button an integer representing the button pressed/released
		 * @param[in] scancode *deprecated*
		 * @param[in] action an integer representing if the button was pressed or released
		 * @param[in] mods *deprecated*
		 */
		static void KeyboardButtonCallback(GLFWwindow* window, int button, int scancode, int action, int mod);
	};

	static std::map<int, bool> buttonPressFlags;
	// serve como buffer do callback, � usado no PollInputEvents pra atualizar as vari�veis relevantes s� uma vez por frame
	static std::vector<Input::buttonEvent> buttonEventsBuffer;

	/**
	 * Checks if the button was pressed
	 * 
	 * @param[in] button an integer representing the button id
	 */
	static bool IsButtonPressed(int button);

	/**
	 * Poll all the input events, calculating the delta, setting the pressed buttons and cleaning the buffer
	 */
	static void PollInputEvents();
};