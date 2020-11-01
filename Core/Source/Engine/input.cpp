#include <input.hpp>

Vector2 Input::Mouse::mousePosition;
Vector2 Input::Mouse::mouseLastPosition;
Vector2 Input::Mouse::mousePositionDelta;
Vector2 Input::Mouse::mousePositionFromCallback;
std::vector<Input::buttonEvent> Input::buttonEventsBuffer;
std::map<int, bool> Input::buttonPressFlags;

void Input::PollInputEvents()
{
	Mouse::mousePositionDelta = Mouse::mousePositionFromCallback - Mouse::mousePosition;
	Mouse::mouseLastPosition = Mouse::mousePosition;
	Mouse::mousePosition = Mouse::mousePositionFromCallback;

	for (Input::buttonEvent event : Input::buttonEventsBuffer)
	{
		Input::buttonPressFlags[event.button] = event.pressed;
	}
	Input::buttonEventsBuffer.clear();
}

void Input::Mouse::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	mousePositionFromCallback = Vector2(xpos, ypos);
}

void Input::Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Input::buttonEvent event;
		event.button = button;
		event.pressed = true;
		Input::buttonEventsBuffer.push_back(event);
	}
	if (action == GLFW_RELEASE)
	{
		Input::buttonEvent event;
		event.button = button;
		event.pressed = false;
		Input::buttonEventsBuffer.push_back(event);
	}
}

void Input::Keyboard::KeyboardButtonCallback(GLFWwindow* window, int button, int scancode, int action, int mod)
{
	if (action == GLFW_PRESS)
	{
		Input::buttonEvent event;
		event.button = button;
		event.pressed = true;
		Input::buttonEventsBuffer.push_back(event);
	}
	if (action == GLFW_RELEASE)
	{
		Input::buttonEvent event;
		event.button = button;
		event.pressed = false;
		Input::buttonEventsBuffer.push_back(event);
	}
}

bool Input::IsButtonPressed(int button)
{
	return Input::buttonPressFlags.count(button) && Input::buttonPressFlags[button];
}