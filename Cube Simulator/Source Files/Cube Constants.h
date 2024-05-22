#include <array>

const int X_AXIS = 0;
const int Y_AXIS = 1;
const int Z_AXIS = 2;

const int WINDOW_WIDTH = 800;		// the width of the game window in pixels
const int WINDOW_HEIGHT = 600;		// the height of the game window in pixels

const float OUTLINE_WIDTH = 25.0;  //The width of the outline around the cube

const float MIN_ZOOM = 8.0;		// the minimum zoom value
const float MAX_ZOOM = 300.0;		// the maximum zoom value

const float MIN_ROTATE = -90.0;	// the minimum rotation value
const float MAX_ROTATE = 90.0;		// the maximum rotation value

const float ROTATE_SCALE = 0.5;	// for converting mouse move events to rotation angle
const float ZOOM_SCALE = 480.0;	// for converting mouse wheel events to zoom level

const int SIDES_ON_A_CUBE = 6;
const int CORNERS_ON_A_CUBE = 8;
const int PIECES_ON_A_CUBE = 27;

const float MAX_COLOUR = 255.0f;

const double ANIMATION_LENGTH = 10.3;
const double SCREEN_SAVER_FACTOR = 10;

const int LEFT = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int UP = 3;
const int BACK = 4;
const int FRONT = 5;

const int L = 0;
const int L_PRIME = 1;
const int R = 2;
const int R_PRIME = 3;
const int D = 4;
const int D_PRIME = 5;
const int U = 6;
const int U_PRIME = 7;
const int B = 8;
const int B_PRIME = 9;
const int F = 10;
const int F_PRIME = 11;
const int X = 12;
const int X_PRIME = 13;
const int Y = 14;
const int Y_PRIME = 15;
const int Z = 16;
const int Z_PRIME = 17;

const int MOVES_NUM = 12;

const std::array<std::array<int, 4>, 6> FACE_CORNERS =
{ {
	{{ 0, 1, 2, 3 }},
	{{ 3, 2, 6, 7 }},
	{{ 1, 2, 6, 5 }},
	{{ 0, 1, 5, 4 }},
	{{ 0, 3, 7, 4 }},
	{{ 7, 6, 5, 4 }}
} };

int arrayChange(int move, int size);

int directionIndexChange(int direction, int arrayWidth);

int directionToAxis(int direction);