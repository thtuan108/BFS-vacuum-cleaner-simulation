#include "Robot.h"
#include "Room.h"

Robot::Robot()
{
	brand = "UIT VB2";
	productCode = "GROUP 4 - WALL-E";
	step = 0;
}

int Robot::getX()
{
	return x;
}

int Robot::getY()
{
	return y;
}

void Robot::showInfor()
{
	cout << "\n\t_______________________________________";
	cout << setfill(' ') << setw(40) << left << "\n\t| VACUUM CLEANER ROBOT WALL-E";
	cout << "|";
	cout << "\n\t|_____________________________________|";
	cout << "\n\t| Brand: " << setfill(' ') << setw(29) << left << brand;
	cout << "|";
	cout << "\n\t|_____________________________________|";
	cout << "\n\t| Product code: " << setfill(' ') << setw(22) << left <<  productCode;
	cout << "|";
	cout << "\n\t|_____________________________________|";
	cout << setprecision(1) << fixed;
	cout << "\n\n\tBattery: " << 100 - (double)step / 1 << "%";
	if (step >= 85)
	{
		cout << "\n\t\t__________________________";
		if (step < 100) cout << "\n\t\t|  !!! LOW BATTERY !!!   |";
		else cout << "\n\t\t| !!! OUT OF BATTERY !!! |";
		cout << "\n\t\t|________________________|";
	}
}

bool Robot::getInRoom(Room& room)
{
	// put Robot in the center of the room, head to the North
	direction = NORTH;
	step = 0;
	x = room.getWidth() / 2;
	y = room.getLength() / 2;

	// if Robot is put at position that has obstable, put it to another position randomly
	// countRand is used to count the number of times Robot is put at ostacled position
	int countRand = 0;
	srand(time(NULL));
	while (room.valueAt(x, y) == 10 && countRand <= 100)
	{
		x = rand() % room.getWidth();
		y = rand() % room.getLength();

		countRand++;
	}

	// if countRand > 100 then check the matrix from front to rear to find free position
	if (room.valueAt(x, y) == 10)
	{
		for (int i = 0; i < room.getWidth(); i++)
		{
			for (int j = 0; j < room.getLength(); j++)
			{
				if (room.valueAt(i, j) != 10)
				{
					x = i;
					y = j;
				}
			}
		}
	}

	// if there is no free position for Robot, then return "false"
	if (room.valueAt(x, y) == 10) return false;
	
	// else, store the position of Robot in the matrix and return "true"
	room.setValue(-1, x, y);
	return true;
}

int Robot::toNorth(Room& room) 
{
	room.setValue(11, x, y); // mark the current position cleaned

	x--;
	room.setValue(-1, x, y);
	direction = NORTH;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	
	if (room.showFloor() == 1) return 1; // finish cleaning, return 1
	else
	{
		int batteryOut = batteryWarning();	// check the battery
		if (batteryOut == 2)	// give robot a rest
			return 2;
		else	// continue to clean
		{
			if (batteryOut == 0) room.describe();
			return 0;
		}
	}
}

int Robot::toEast(Room& room) 
{
	room.setValue(11, x, y); // mark the current position cleaned

	y++;
	room.setValue(-2, x, y);
	direction = EAST;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	if (room.showFloor() == 1) return 1; // finish cleaning, return 1
	else
	{
		int batteryOut = batteryWarning();	// check the battery
		if (batteryOut == 2)	// give robot a rest
			return 2;
		else	// continue to clean
		{
			if (batteryOut == 0)room.describe();
			return 0;
		}
	}
}

int Robot::toWest(Room& room) 
{
	room.setValue(11, x, y); // mark the current position cleaned

	y--;
	room.setValue(-3, x, y);
	direction = WEST;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	if (room.showFloor() == 1) return 1; // finish cleaning, return 1
	else
	{
		int batteryOut = batteryWarning();	// check the battery
		if (batteryOut == 2)	// give robot a rest
			return 2;
		else	// continue to clean
		{
			if (batteryOut == 0)room.describe();
			return 0;
		}
	}
}

int Robot::toSouth(Room& room) 
{
	room.setValue(11, x, y); // mark the current position cleaned

	x++;
	room.setValue(-4, x, y);
	direction = SOUTH;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	if (room.showFloor() == 1) return 1; // finish cleaning, return 1
	else
	{
		int batteryOut = batteryWarning();	// check the battery
		if (batteryOut == 2)	// give robot a rest
			return 2;
		else	// continue to clean
		{
			if (batteryOut == 0)room.describe();
			return 0;
		}
	}
}

int Robot::batteryWarning()
{
	if (step == 100)
	{
		cout << "\n\t\t************************************************************";
		cout << "\n\t\t\t!!! OUT OF BATTERY !!! PLEASE CHOOSE ONE OF THE OPTIONS BELOW:";
		cout << "\n\t\t\t 1. Charge and continue to work";
		cout << "\n\t\t\t 2. Give Robot a rest";
		cout << "\n\t\t\t => Your choice: ";
		int option;
		cin >> option;

		while (option != 1 && option != 2)
		{
			cout << "\n\t\t=> This choice is invalid, please choose again: ";
			cin >> option;
		}

		if (option == 1)
		{
			step = 0;
			cout << "\t\t\t_____________________________";
			cout << "\n\t\t\t| ... ROBOT IS CHARGING ... |";
			cout << "\n\t\t\t|___________________________|\n\n";
			Sleep(1000);
		}
		return option;
	}
	return 0;
}

// find route to the nearest uncleaned square using BFS
vector<int> Robot::findRoute(Room& room)
{
	int** trace = new int* [room.getWidth()];
	for (int i = 0; i < room.getWidth(); i++)
	{
		trace[i] = new int[room.getLength()];
		for (int j = 0; j < room.getLength(); j++)
			trace[i][j] = 10;
	}
	trace[x][y] = -1;

	int xDirect[4] = { 0,1,-1,0 };
	int yDirect[4] = { -1,0,0,1 };
	// elements at index 0, 1, 2, 3 represent West, South, North, East repectively

	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	pair<int, int> des;

	bool found = false;
	while (!q.empty())
	{
		pair<int, int> pos = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
			if (room.valueAt(pos.first + xDirect[i], pos.second + yDirect[i]) != 10
				&& trace[pos.first + xDirect[i]][pos.second + yDirect[i]] == 10)
			{
				trace[pos.first + xDirect[i]][pos.second + yDirect[i]] = i;
				if (room.valueAt(pos.first + xDirect[i], pos.second + yDirect[i]) < 10)
				{
					found = true;
					des = make_pair(pos.first + xDirect[i], pos.second + yDirect[i]);
					break;
				}
				else
				{
					q.push(make_pair(pos.first + xDirect[i], pos.second + yDirect[i]));
				}
			}

		if (found) break;
	}

	vector<int> route;
	if (!found) return route;

	while (trace[des.first][des.second] != -1)
	{
		int i = trace[des.first][des.second];
		route.push_back(i);
		des.first -= xDirect[i];
		des.second -= yDirect[i];
	}
	return route;
}

int Robot::move(Room& room, vector<int> route)
{
	for (int i = route.size() - 1; i >= 0; i--)
	{
		int output;
		switch (route[i])
		{
		case 0:
			output = toWest(room);
			if (output != 0) return output;
			break;
		case 1:
			output = toSouth(room);
			if (output != 0) return output;
			break;
		case 2:
			output = toNorth(room);
			if (output != 0) return output;
			break;
		case 3:
			output = toEast(room);
			if (output != 0) return output;
			break;
		}
	}

	return 0;
}

void Robot::run(Room& room)
{
	vector<int> route = findRoute(room);
	while (!route.empty())
	{
		int output = move(room, route);
		if (output == 1)
		{
			cout << "\t\t___________________________________________________";
			cout << "\n\t\t| FINISHED CLEANING! THANKS FOR USING OUT SERVICE |";
			cout << "\n\t\t|_________________________________________________|\n\n";
			return;
		}
		else if (output == 2)
		{
			cout << "\t\t______________________________________";
			cout << "\n\t\t| THANK YOU! ROBOT WILL BE BACK SOON |";
			cout << "\n\t\t|____________________________________|\n\n";
			return;
		}

		route = findRoute(room);
	}
	cout << "\t\t___________________________________________________________";
	cout << "\n\t\t| TOO MANY FURNITURE IN THE ROOM! CLEANING CANNOT BE DONE |";
	cout << "\n\t\t|_________________________________________________________|\n\n";
}