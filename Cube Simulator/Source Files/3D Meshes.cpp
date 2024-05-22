#include <iostream>		// for string, cin, cout and endl
#include <glut.h>		// the library for glut (OpenGL)

#include "ICS_Game.h"	// for the simple game framework

// constants
const int WINDOW_WIDTH = 800;		// the width of the game window in pixels
const int WINDOW_HEIGHT = 600;		// the height of the game window in pixels

const float MIN_ZOOM = 2.0f;		// the minimum zoom value
const float MAX_ZOOM = 6.0f;		// the maximum zoom value

const float MIN_ROTATE = -90.0f;	// the minimum rotation value
const float MAX_ROTATE = 90.0f;		// the maximum rotation value

const float ROTATE_SCALE = 0.5f;	// for converting mouse move events to rotation angle
const float ZOOM_SCALE = 480.0f;	// for converting mouse wheel events to zoom level

// global variables
float zoom = MAX_ZOOM;				// the number of units to position the camera away from the origin along the z-axis

float rotateXAngle = 0;			// the number of degrees to rotate the model around the x-axis
float rotateYAngle = 0;			// the number of degrees to rotate the model around the y-axis

int rotateXStart = 0;			// the x position of the mouse when rotation began
int rotateYStart = 0;			// the y position of the mouse when rotation began

float rotateXAngleStart = 0;	// the x rotation when rotation began
float rotateYAngleStart = 0;	// the y rotation when rotation began

bool rotateModel = false;		// indicates the model is being rotated

/**
 * This renders 3D game elements.
 */
void render3D()
{
	glColor3f(1.0f, 1.0f, 1.0f);				// set the drawing color to white
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// set the render mode to wireframe
	
	glTranslatef(0.0f, 0.0f, -zoom);			// position the camera on the z-axis
	glRotatef(rotateXAngle, 1.0f, 0.0f, 0.0f);	// rotate the model around the x-axis
	glRotatef(rotateYAngle, 0.0f, 1.0f, 0.0f);	// rotate the model around the y-axis

	/*******************************************************************
	 * delete the following example and render the current mesh instead
	 *******************************************************************/
	 
	glBegin(GL_TRIANGLES);				// this starts drawing triangles.  every 3 vertices between
										// here and glEnd() will be rendered on screen as a triangle

	glVertex3f(-1.0f, -1.0f, 0.0f);		// the first vertex of the triangle
	glVertex3f(1.0f, -1.0f, 0.0f);		// the second vertex of the triangle
	glVertex3f(0.0f, 1.0f, 0.0f);		// the third vertex of the triangle

	glEnd();							// the stops drawing triangles
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
	if (rotateModel)
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
		rotateModel = (eventType == ICS_EVENT_PRESS);
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
	if (zoom < MIN_ZOOM)
	{
		zoom = MIN_ZOOM;
	}
	
	if (zoom > MAX_ZOOM)
	{
		zoom = MAX_ZOOM;
	}
}

/**
 * The callback for handling exiting the program.
 */
void handleExit()
{
	/**************************
	 * delete allocated memory
	 **************************/
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
	/****************************************
	 * load data from file and create meshes
	 ****************************************/
	 
	// create the game and set the callbacks
	ICS_Game::getInstance().setRender3DEventCallback(render3D);						// set the callback for rendering 3D game elements
	ICS_Game::getInstance().setMouseMoveEventCallback(handleMouseMove);				// set the callback for handling mouse move events
	ICS_Game::getInstance().setMouseWheelEventCallback(handleMouseWheel);			// set the callback for handling mouse wheel events
	ICS_Game::getInstance().setMouseButtonEventCallback(handleMouseButtonEvent);	// set callback for mouse button events
	ICS_Game::getInstance().setExitEventCallback(handleExit);						// set the callback for exiting the program

	// start the game... the program ends when this function returns (when the game loop ends)
	return ICS_Game::getInstance().go("OpenGL", WINDOW_WIDTH, WINDOW_HEIGHT);
}
