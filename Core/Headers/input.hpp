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
		// serve como buffer do callback, é usado no PollInputEvents pra atualizar as variáveis relevantes só uma vez por frame
		static Vector2 mousePositionFromCallback;

		static Vector2 mousePosition;
		static Vector2 mouseLastPosition;
		static Vector2 mousePositionDelta;

		static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
	
	class Keyboard
	{
	public:
		static void KeyboardButtonCallback(GLFWwindow* window, int button, int scancode, int action, int mod);
	};

	static std::map<int, bool> buttonPressFlags;
	// serve como buffer do callback, é usado no PollInputEvents pra atualizar as variáveis relevantes só uma vez por frame
	static std::vector<Input::buttonEvent> buttonEventsBuffer;
	static bool IsButtonPressed(int button);
	static void PollInputEvents();
};