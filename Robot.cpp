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
	cout << setfill(' ') << setw(40) << left << "\n\t| ROBOT HUT BUI WALL-E";
	cout << "|";
	cout << "\n\t|_____________________________________|";
	cout << "\n\t| Nhan hieu: " << setfill(' ') << setw(25) << left << brand;
	cout << "|";
	cout << "\n\t|_____________________________________|";
	cout << "\n\t| Ma so san pham: " << setfill(' ') << setw(20) << left <<  productCode;
	cout << "|";
	cout << "\n\t|_____________________________________|";
	cout << setprecision(1) << fixed;
	cout << "\n\n\tMuc pin hien tai: " << 100 - (double)step / 1 << "%";
	if (step >= 85)
	{
		cout << "\n\t\t___________________";
		if (step < 100) cout << "\n\t\t| !!! PIN YEU !!! |";
		else cout << "\n\t\t| !!! HET PIN !!! |";
		cout << "\n\t\t|_________________|";
	}
}

bool Robot::getInRoom(Room& room)
{
	// dat robot o vi tri trung tam, huong ve phia Bac
	direction = NORTH;
	step = 0;
	x = room.getWidth() / 2;
	y = room.getLength() / 2;

	// neu robot roi vao o co chuong ngai vat thi nhay sang o khac (random)
	// dung bien countRand de dem so lan random roi vao o chuong ngai vat
	// neu countRand > 100 thi duyet lai tu dau den cuoi ma tran
	int countRand = 0;
	srand(time(NULL));
	while (room.valueAt(x, y) == 10 && countRand <= 100)
	{
		x = rand() % room.getWidth();
		y = rand() % room.getLength();

		countRand++;
	}

	// neu robot van roi vao o chuong ngai vat => duyet ma tran tu dau den cuoi
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

	// neu khong the tim duoc vi tri cho robot tren ma tra, tra ve "false"
	if (room.valueAt(x, y) == 10) return false;
	
	//nguoc lai, tra ve "true"
	room.setValue(-1, x, y); // danh dau vi tri robot tren ma tran
	return true;
}

int Robot::toNorth(Room& room) 
{
	room.setValue(11, x, y); // danh dau o hien tai la da di qua

	x--;
	room.setValue(-1, x, y);
	direction = NORTH;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	
	if (room.showFloor() == 1) return 1; // da hoan tat don dep
	else
	{
		int batteryOut = batteryWarning();	// kiem tra pin
		if (batteryOut == 2)	// cho robot nghi ngoi
			return 2;
		else	// tiep tuc don dep
		{
			if (batteryOut == 0) room.describe();
			return 0;
		}
	}
}

int Robot::toEast(Room& room) 
{
	room.setValue(11, x, y); // danh dau o hien tai la da di qua

	y++;
	room.setValue(-2, x, y);
	direction = EAST;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	if (room.showFloor() == 1) return 1; // da hoan tat don dep
	else
	{
		int batteryOut = batteryWarning();	// kiem tra pin
		if (batteryOut == 2)	// cho robot nghi ngoi
			return 2;
		else	// tiep tuc don dep
		{
			if (batteryOut == 0)room.describe();
			return 0;
		}
	}
}

int Robot::toWest(Room& room) 
{
	room.setValue(11, x, y); // danh dau o hien tai la da di qua

	y--;
	room.setValue(-3, x, y);
	direction = WEST;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	if (room.showFloor() == 1) return 1; // da hoan tat don dep
	else
	{
		int batteryOut = batteryWarning();	// kiem tra pin
		if (batteryOut == 2)	// cho robot nghi ngoi
			return 2;
		else	// tiep tuc don dep
		{
			if (batteryOut == 0)room.describe();
			return 0;
		}
	}
}

int Robot::toSouth(Room& room) 
{
	room.setValue(11, x, y); // danh dau o hien tai la da di qua

	x++;
	room.setValue(-4, x, y);
	direction = SOUTH;
	step++;

	Sleep(200);
	system("cls");
	showInfor();
	if (room.showFloor() == 1) return 1; // da hoan tat don dep
	else
	{
		int batteryOut = batteryWarning();	// kiem tra pin
		if (batteryOut == 2)	// cho robot nghi ngoi
			return 2;
		else	// tiep tuc don dep
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
		cout << "\n\t\t\t!!! HET PIN !!! MOI QUY KHACH LUA CHON TINH NANG:";
		cout << "\n\t\t\t 1. Sac pin va tiep tuc don dep";
		cout << "\n\t\t\t 2. Cho robot nghi ngoi";
		cout << "\n\t\t\t => Lua chon cua quy khach: ";
		int option;
		cin >> option;

		while (option != 1 && option != 2)
		{
			cout << "\n\t\t=> Lua chon khong hop le, moi chon lai: ";
			cin >> option;
		}

		if (option == 1)
		{
			step = 0;
			cout << "\t\t\t__________________________";
			cout << "\n\t\t\t| ... ROBOT DANG SAC ... |";
			cout << "\n\t\t\t|________________________|\n\n";
			Sleep(1000);
		}
		return option;
	}
	return 0;
}

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
	// cac phan tu tai vi tri 0, 1, 2, 3 tuong ung Tay, Nam, Bac, Dong

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
			cout << "\t\t___________________________________________________________";
			cout << "\n\t\t| DA DON DEP XONG! CAM ON QUY KHACH DA TIN TUONG SU DUNG! |";
			cout << "\n\t\t|_________________________________________________________|\n\n";
			return;
		}
		else if (output == 2)
		{
			cout << "\t\t_______________________________________________";
			cout << "\n\t\t| CAM ON QUY KHACH! ROBOT SE SOM PHUC VU LAI! |";
			cout << "\n\t\t|_____________________________________________|\n\n";
			return;
		}

		route = findRoute(room);
	}
	cout << "\t\t_______________________________________________________";
	cout << "\n\t\t| PHONG QUA NHIEU DO DAC! KHONG THE HOAN TAT DON DEP! |";
	cout << "\n\t\t|_____________________________________________________|\n\n";
}