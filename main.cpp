#include <iostream>
#include "Room.h"
#include "Robot.h"
using namespace std;

int main()
{
	Robot robot;
	robot.showInfor();

	int width, length;
	cout << "\n\n\tEnter the room's information: ";
	cout << "\n\tWidth: ";
	cin >> width;
	cout << "\tLength: ";
	cin >> length;

	Room room(width, length);
	room.initializeRoom(robot);
	
	system("cls");
	robot.showInfor();
	room.showFloor();

	robot.run(room);

	return 0;
}