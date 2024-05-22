#include <iostream>		// for string, cin, cout and endl
#include <glut.h>		// the library for glut (OpenGL)

#include "ICS_Game.h"	// for the simple game framework
#include "Cube.h"		// for cube class


// global variables
float zoom = -6.0f;				// the number of units to position the camera away from the origin along the z-axis

float rotateXAngle = 30;		// the number of degrees to rotate the model around the x-axis
float rotateYAngle = -30;		// the number of degrees to rotate the model around the y-axis

int rotateXStart = 0;			// the x position of the mouse when rotation began
int rotateYStart = 0;			// the y position of the mouse when rotation began

float rotateXAngleStart = 0;	// the x rotation when rotation began
float rotateYAngleStart = 0;	// the y rotation when rotation began

bool rotateView = false;		// indicates the model is being rotated

const Colour CUBE_COLOURS[SIDES] = { Colour(255, 255, 255), Colour(0, 255, 0), Colour(255, 0, 0), Colour(255, 255, 0), Colour(0, 0, 255), Colour(255, 128, 0) };
const Colour BLACK = Colour(0.0f, 0.0f, 0.0f);

Cube cube = Cube(CUBE_COLOURS, 1.0f, Point(), true, BLACK);
Cube cube2 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, 0.0f, 0.0f), true, BLACK);
Cube cube3 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, 0.0f, 0.0f), true, BLACK);
Cube cube4 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, 1.0f, 0.0f), true, BLACK);
Cube cube5 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, 1.0f, 0.0f), true, BLACK);
Cube cube6 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, 1.0f, 0.0f), true, BLACK);
Cube cube7 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, -1.0f, 0.0f), true, BLACK);
Cube cube8 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, -1.0f, 0.0f), true, BLACK);
Cube cube9 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, -1.0f, 0.0f), true, BLACK);

Cube cube10 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, 0.0f, 1.0f), true, BLACK);
Cube cube11 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, 0.0f, 1.0f), true, BLACK);
Cube cube12 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, 0.0f, 1.0f), true, BLACK);
Cube cube13 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, 1.0f, 1.0f), true, BLACK);
Cube cube14 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, 1.0f, 1.0f), true, BLACK);
Cube cube15 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, 1.0f, 1.0f), true, BLACK);
Cube cube16 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, -1.0f, 1.0f), true, BLACK);
Cube cube17 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, -1.0f, 1.0f), true, BLACK);
Cube cube18 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, -1.0f, 1.0f), true, BLACK);

Cube cube19 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, 0.0f, -1.0f), true, BLACK);
Cube cube20 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, 0.0f, -1.0f), true, BLACK);
Cube cube21 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, 0.0f, -1.0f), true, BLACK);
Cube cube22 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, 1.0f, -1.0f), true, BLACK);
Cube cube23 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, 1.0f, -1.0f), true, BLACK);
Cube cube24 = Cube(CUBE_COLOURS, 1.0f, Point(-1.0f, 1.0f, -1.0f), true, BLACK);
Cube cube25 = Cube(CUBE_COLOURS, 1.0f, Point(0.0f, -1.0f, -1.0f), true, BLACK);
Cube cube26 = Cube(CUBE_COLOURS, 1.0f, Point(1.0f, -1.0f, -1.0f), true, BLACK);
Cube cube27 = Cube(CUBE_COLOURS, 1.5f, Point(-1.0f, -1.0f, -1.0f), true, BLACK);

/**
 * This renders 3D game elements.
 */
void handleRender3D()
{
	glTranslatef(0.0f, 0.0f, zoom);				// position the camera on the z-axis
	glRotatef(rotateXAngle, 1.0f, 0.0f, 0.0f);	// rotate the model around the x-axis
	glRotatef(rotateYAngle, 0.0f, 1.0f, 0.0f);	// rotate the model around the y-axis

	cube.draw(zoom);
	cube2.draw(zoom);
	cube3.draw(zoom);
	cube4.draw(zoom);
	cube5.draw(zoom);
	cube6.draw(zoom);
	cube7.draw(zoom);
	cube8.draw(zoom);
	cube9.draw(zoom);
	cube10.draw(zoom);
	cube11.draw(zoom);
	cube12.draw(zoom);
	cube13.draw(zoom);
	cube14.draw(zoom);
	cube15.draw(zoom);
	cube16.draw(zoom);
	cube17.draw(zoom);
	cube18.draw(zoom);
	cube19.draw(zoom);
	cube20.draw(zoom);
	cube21.draw(zoom);
	cube22.draw(zoom);
	cube23.draw(zoom);
	cube24.draw(zoom);
	cube25.draw(zoom);
	cube26.draw(zoom);
	cube27.draw(zoom);
}

/**
 * This handles mouse move events.
 *
 * @param mouseX		The x position of the mouse cursor.
 * @param mouseY		The y position of the mouse cursor.
 */
void handleMouseMove(int mouseX, int mouseY)
{
	// check if the model is being rotated
	if (rotateView)
	{
		// update the rotation based on mouse movement
		rotateXAngle = rotateXAngleStart + (mouseY - rotateYStart) * ROTATE_SCALE;
		rotateYAngle = rotateYAngleStart + (mouseX - rotateXStart) * ROTATE_SCALE;

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
void handleMouseButtonEvent(int mouseButton, int mouseX, int mouseY, int eventType)
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

	/*****************************************************************
	 * switch to the next mesh when the right mouse button is clicked
	 *****************************************************************/
}

/**
 * This handles mouse wheel events.
 *
 * @param mouseX	The x position of the mouse cursor.
 * @param mouseY	The y position of the mouse cursor.
 * @param rotation	The wheel rotation value.  A positive value indicates that the wheel was rotated forward, away
 *					from the user; a negative value indicates that the wheel was rotated backward, toward the user.
 */
void handleMouseWheel(int mouseX, int mouseY, int rotation)
{
	// update the zoom level when the mouse wheel is rotated
	zoom -= rotation / ZOOM_SCALE;

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

/**
 * The callback for handling exiting the program.
 */
void handleExit()
{
	bool l = true;
	/**************************
	 * delete allocated memory
	 **************************/
}

void handleWindowResize(int height, int width)
{
	
}

void handleKeyboardEvent(int key, int eventType)
{

}
 
void update(float elapsed)
{

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
	ICS_Game::getInstance().setExitEventCallback(handleExit);						// set the callback for exiting the program
	ICS_Game::getInstance().setWindowResizeEventCallback(handleWindowResize);
	ICS_Game::getInstance().setKeyboardEventCallback(handleKeyboardEvent);
	ICS_Game::getInstance().setUpdateEventCallback(update);

	// start the game... the program ends when this function returns (when the game loop ends)
	return ICS_Game::getInstance().go("Cube Simulator", WINDOW_WIDTH, WINDOW_HEIGHT);
}
