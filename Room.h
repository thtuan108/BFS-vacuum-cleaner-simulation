#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
#include "Robot.h"
using namespace std;

class Room {

private:
	int** floor;	
	// floor is 2D matrix representing the room chart
	// Values in the elements represent the position situation
	// -1     : Robot's current position, head to the North
	// -2     : Robot's current position, head to the East
	// -3     : Robot's current position, head to the West
	// -4     : Robot's current position, head to the South
	// 0 -> 9 : Uncleaned position
	// 10     : Obstacle
	// 11     : Cleaned position

	int width;
	int length;

public:
	Room() {};
	Room(int, int);

	int getWidth();
	int getLength();
	int valueAt(int, int);			// get the value of a position in matrix
	void setValue(int, int, int);	// assign a value for a position in matrix

	void initializeGrid();			// randomly initialize a grid
	bool initializeRoom(Robot&);	// create a room chart using values in the grid
	void describe();				// explain meaning of symbols in the chart
	int showFloor();				// display current state of room chart, return 1 if succeed
};

