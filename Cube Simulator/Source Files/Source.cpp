#include <iostream>		// for string, cin, cout and endl

#include "ICS_Game.h"	// for the simple game framework
#include "Rubiks.h"		// for cube class

#include <glut.h>		// the library for glut (OpenGL)

//Getting cube to turn
//Add delay to rotation for queueing moves
//Add rest of the moves to keybindings

// global variables
float zoom = -MIN_ZOOM;			// the number of units to position the camera away from the origin along the z-axis

float rotateXAngle = 16.0f;		// the number of degrees to rotate the model around the x-axis
float rotateYAngle = -21.0f;	// the number of degrees to rotate the model around the y-axis

int rotateXStart = 0;			// the x position of the mouse when rotation began
int rotateYStart = 0;			// the y position of the mouse when rotation began

float rotateXAngleStart = 0.0f;	// the x rotation when rotation began
float rotateYAngleStart = 0.0f;	// the y rotation when rotation began

bool rotateView = false;		// indicates the camera is being rotated

float duration = 0.0f;
float lastTime = 0.0f;

Point* point = new Point();
const Colour* BLACK = new Colour();

bool clockwise = true;

Rubiks <3>cube(*point, 3.0, CUBE_COLOURS, BLACK);

Cube other;

/**
 * This renders 3D game elements.
 */
static void handleRender3D()
{
	glTranslatef(0.0f, 0.0f, zoom);				// position the camera on the z-axis
	glRotatef(rotateXAngle, 1.0f, 0.0f, 0.0f);	// rotate the model around the x-axis
	glRotatef(rotateYAngle, 0.0f, 1.0f, 0.0f);	// rotate the model around the y-axis

	cube.draw(zoom);
	//other.draw(zoom);
}

/**
 * This handles mouse move events.
 *
 * @param mouseX		The x position of the mouse cursor.
 * @param mouseY		The y position of the mouse cursor.
 */
static void handleMouseMove(int mouseX, int mouseY)
{
	// check if the model is being rotated
	if (rotateView)
	{
		// update the rotation based on mouse movement
		rotateXAngle = rotateXAngleStart + float(mouseY - rotateYStart) * ROTATE_SCALE;
		rotateYAngle = rotateYAngleStart + float(mouseX - rotateXStart) * ROTATE_SCALE;

		// limit rotations so things don't go wonky
		if (rotateXAngle > MAX_ROTATE)
		{
			rotateXAngle = MAX_ROTATE;
		}

		if (rotateXAngle < MIN_ROTATE)
		{
			rotateXAngle = MIN_ROTATE;
		}
	}
}

/**
 * This handles mouse button events.
 *
 * @param mouseButton	The button triggered the event (ICS_LEFT_MOUSE_BUTTON, ICS_RIGHT_MOUSE_BUTTON or ICS_MIDDLE_MOUSE_BUTTON)
 * @param mouseX		The x position of the mouse cursor.
 * @param mouseY		The y position of the mouse cursor.
 * @param eventType		The type of event (ICS_EVENT_PRESS or ICS_EVENT_RELEASE)
 */
static void handleMouseButtonEvent(int mouseButton, int mouseX, int mouseY, int eventType)
{
	// activate rotating the model when the left mouse button is clicked
	if (mouseButton == ICS_LEFT_MOUSE_BUTTON)
	{
		if (eventType == ICS_EVENT_PRESS)
		{
			// keep track of the mouse coordinates
			rotateXStart = mouseX;
			rotateYStart = mouseY;

			// keep track of the current rotation angles
			rotateXAngleStart = rotateXAngle;
			rotateYAngleStart = rotateYAngle;
		}

		// toggle rotation
		rotateView = (eventType == ICS_EVENT_PRESS);
	}
}

/**
 * This handles mouse wheel events.
 *
 * @param mouseX	The x position of the mouse cursor.
 * @param mouseY	The y position of the mouse cursor.
 * @param rotation	The wheel rotation value.  A positive value indicates that the wheel was rotated forward, away
 *					from the user; a negative value indicates that the wheel was rotated backward, toward the user.
 */
static void handleMouseWheel(int, int, int rotation)
{
	// update the zoom level when the mouse wheel is rotated
	zoom -= float(rotation) / ZOOM_SCALE;

	// limit the zoom values
	if (zoom > -MIN_ZOOM)
	{
		zoom = -MIN_ZOOM;
	}

	if (zoom < -MAX_ZOOM)
	{
		zoom = -MAX_ZOOM;
	}
}

static void handleKeyboardEvent(int key, int eventType)
{
	if (eventType == ICS_EVENT_PRESS)
	{
		cube.getMove(key);
	}
}

static void update(float elapsed)
{
	cube.update(elapsed);
}

/**
 * This is the entry point to the program.
 *
 * @param hInstance			A handle to the current instance of the application.
 * @param hPrevInstance		A handle to the previous instance of the application.
 * @param lpCmdLine			The command line for the application, excluding the program name.
 * @param nCmdShow			Controls how the window will be shown.
 *
 *@returns					If the function succeeds, terminating when it receives a WM_QUIT message, it should return the exit value contained
 *							in that message's wParam parameter.  If the function terminates before entering the message loop, it should return zero.
 */
#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	// create the game and set the callbacks
	ICS_Game::getInstance().setRender3DEventCallback(handleRender3D);				// set the callback for rendering 3D game elements
	ICS_Game::getInstance().setMouseMoveEventCallback(handleMouseMove);				// set the callback for handling mouse move events
	ICS_Game::getInstance().setMouseWheelEventCallback(handleMouseWheel);			// set the callback for handling mouse wheel events
	ICS_Game::getInstance().setMouseButtonEventCallback(handleMouseButtonEvent);	// set callback for mouse button events
	ICS_Game::getInstance().setKeyboardEventCallback(handleKeyboardEvent);
	ICS_Game::getInstance().setUpdateEventCallback(update);

	// start the game... the program ends when this function returns (when the game loop ends)
	return ICS_Game::getInstance().go("Cube Simulator", WINDOW_WIDTH, WINDOW_HEIGHT);
}