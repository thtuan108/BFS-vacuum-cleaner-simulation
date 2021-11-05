#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

class Room;

enum Direction
{
	NORTH, SOUTH, EAST, WEST
};

class Robot {

private:
	// Coordination of Robot in the room
	int x;	// row number
	int y;	// column number
	Direction direction;	// current direction
	int step;				// number of steps Robot has made

	string brand;
	string productCode;

	int toNorth(Room&);		// to the North, return 1 if cleaning is done
	int toEast(Room&);		// to the East, return 1 if cleaning is done
	int toWest(Room&);		// to the West, return 1 if cleaning is done
	int toSouth(Room&);		// to the South, return 1 if cleaning is done

	int batteryWarning();			// check battery and ask for options
	vector<int> findRoute(Room&);	// find best route to nearest uncleaned position
	int move(Room&, vector<int>);	// move using the route given

public:
	Robot();

	int getX();
	int getY();

	void showInfor();		// display Robot's information
	bool getInRoom(Room&);	// put Robot into the room, head to the North, return 1 if succeed

	void run(Room&);
};