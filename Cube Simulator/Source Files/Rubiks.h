#ifndef RUBIKS_H
#define RUBIKS_H

#include "Cube.h"

template <int WIDTH>
class Rubiks
{
	const unsigned int CUBIES_NUM = pow(WIDTH, 3);
	std::vector<Cube*> _cubies;
	Point _centre;
	std::array<Colour, SIDES_ON_A_CUBE> _faceColours;
	const Colour* _outlineColour = nullptr;
	double _width = 1.0;
	int _moveNum = 0;
	RotationManager _manager;

public:

	Rubiks()
	{
		_cubies.resize(CUBIES_NUM);
		for (auto& i : _cubies)
		{
			i = new Cube(CUBE_COLOURS, 1.0, &_centre);
		}
	}

	Rubiks(const Point& centre, double width, const std::array<Colour, SIDES_ON_A_CUBE>& faceColours, const Colour* outlineColour = nullptr) :
		_centre(centre),
		_width(width / WIDTH),
		_faceColours(faceColours),
		_outlineColour(outlineColour ? new Colour(*outlineColour) : outlineColour)
	{
		_cubies.resize(CUBIES_NUM);
		double shift = (WIDTH - 1) / 2;
		for (int i = 0; i < CUBIES_NUM; i++)
		{
			double xLevel = (double)(i % (int)WIDTH - shift) * _width;
			double yLevel = (double)(i / (int)pow((int)WIDTH, 2) - shift) * _width * -1;
			double zLevel = (double)(i % (int)pow((int)WIDTH, 2) / (int)WIDTH - shift) * _width;

			auto cubeCentre = Point(xLevel, yLevel, zLevel) + centre;

			_cubies[i] = new Cube(_faceColours, _width, cubeCentre, _outlineColour);
		}
	}

	Rubiks(const Rubiks& copy) :
		_centre(copy._centre),
		_width(copy._width / WIDTH),
		_faceColours(copy._faceColours),
		_outlineColour(copy._outlineColour ? new Colour(*copy._outlineColour) : copy._outlineColour)
	{
		_cubies.resize(CUBIES_NUM);
		for (int i = 0; i < CUBIES_NUM; i++)
		{
			_cubies[i] = new Cube(*copy._cubies[i]);
		}
	}

	Rubiks& operator=(const Rubiks& copy)
	{
		_centre = copy._centre;
		_width = copy._width / WIDTH;
		_faceColours = copy._faceColours;
		_outlineColour = copy._outlineColour ? new Colour(*copy._outlineColour) : copy._outlineColour;

		_cubies.resize(CUBIES_NUM);
		for (int i = 0; i < CUBIES_NUM; i++)
		{
			_cubies[i] = new Cube(*copy._cubies[i]);
		}
	}

	void draw(double zoom)
	{
		for (int i = 0; i < CUBIES_NUM; i++)
		{
			_cubies[i]->draw(zoom);
		}
	}

	void update(double elapsed)
	{
		_manager.update(elapsed);
	}

	void getMove(int key)
	{
		int move = 0;

		if (key == ICS_KEY_D)
		{
			move = L;
		}
		else if (key == ICS_KEY_E)
		{
			move = L_PRIME;
		}
		else if (key == ICS_KEY_I)
		{
			move = R;
		}
		else if (key == ICS_KEY_K)
		{
			move = R_PRIME;
		}
		else if (key == ICS_KEY_S)
		{
			move = D;
		}
		else if (key == ICS_KEY_L)
		{
			move = D_PRIME;
		}
		else if (key == ICS_KEY_J)
		{
			move = U;
		}
		else if (key == ICS_KEY_F)
		{
			move = U_PRIME;
		}
		else if (key == ICS_KEY_W)
		{
			move = B;
		}
		else if (key == ICS_KEY_O)
		{
			move = B_PRIME;
		}
		else if (key == ICS_KEY_H)
		{
			move = F;
		}
		else if (key == ICS_KEY_G)
		{
			move = F_PRIME;
		}
		else if (key == ICS_KEY_SEMICOLON)
		{
			move = Y;
		}
		else if (key == ICS_KEY_A)
		{
			move = Y_PRIME;
		}
		else if (key == ICS_KEY_T or key == ICS_KEY_Y)
		{
			move = X;
		}
		else if (key == ICS_KEY_B)
		{
			move = X_PRIME;
		}
		else if (key == ICS_KEY_P)
		{
			move = Z;
		}
		else if (key == ICS_KEY_Q)
		{
			move = Z_PRIME;
		}
		else
		{
			return;
		}

		if (move < MOVES_NUM)
		{
			turn(move);
		}
		else
		{
			rotate(move);
		}
		_moveNum++;
	}

private:

	void rotate(int move)
	{
		int axis = (move - MOVES_NUM) / 2;
		bool clockwise = (move - MOVES_NUM) % 2 == 0;
		for (int i = 0; i < CUBIES_NUM; i++)
		{
			_cubies[i]->startRotation(axis, _moveNum, _manager, clockwise, _centre);
		}
	}

	void turn(int move)
	{
		bool clockwise = move % 2 == 0;
		int axis = directionToAxis(int(move / 2));

		auto* indexArray = new int[pow(WIDTH, 2)];

		std::shared_ptr<Rotation> preceedingRotation(nullptr);

		for (int i = 0; i < pow(WIDTH, 2); i++)
		{
			if (axis == X_AXIS)
			{
			}
			else if (axis == Y_AXIS)
			{
			}
			else if (axis == Z_AXIS)
			{
			}
		}

		for (int i = 0; i < pow(WIDTH, 2); i++)
		{
			if (axis == X_AXIS)
			{
				_cubies[i * WIDTH]->startRotation(axis, _moveNum, _manager, clockwise, _centre);
			}
			else if (axis == Y_AXIS)
			{
				_cubies[i]->startRotation(axis, _moveNum, _manager, clockwise, _centre);
			}
			else if (axis == Z_AXIS)
			{
				int index = i / WIDTH * pow(WIDTH, 2) + i % WIDTH + pow(WIDTH, 2) - WIDTH;
				_cubies[index]->startRotation(axis, _moveNum, _manager, clockwise, _centre);
			}
		}
		updateArray(move);
	}

	void updateArray(int move)
	{
		for (int i = 0; i < pow(WIDTH, 2); i++)
		{
			//calculateNewPositionOnCube(WIDTH, move, i, )
			//swap<Cube*>(_cubies[ARRAY_CHANGES[move][i][0]], _cubies[ARRAY_CHANGES[move][i][1]]);
		}
	}
};

#endif // !RUBIKS_H
