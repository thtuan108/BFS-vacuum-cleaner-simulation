#include "Room.h"

Room::Room(int x, int y)
{
	width = x;
	length = y;

	initializeGrid(); // khoi tao ma tran ngau nhien
}

int Room::getWidth()
{
	return width;
}

int Room::getLength()
{
	return length;
}

void Room::initializeGrid() {
	
	// Tao ma tran ngau nhien
	floor = new int*[width];
	
	srand(time(NULL));
	for (int i = 0; i < width; i++) 
	{
		floor[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			floor[i][j] = rand() % 10; // khoi tao cac o co gia tri [0, 9]
		}
	}
}

bool Room::initializeRoom(Robot& robot)
{
	// Tao cac vat can dang khoi
	// => thay cac o xung quanh 9 thanh 10 de tao cac chuong ngai vat dang khoi
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (floor[i][j] == 9 && i % 3 == 0)
			{
				if (i > 0)
				{
					floor[i - 1][j] = 10;
					
					if (j > 0)
					{
						floor[i - 1][j - 1] = 10;
					}
				}
				if (j > 0)
				{
					floor[i][j - 1] = 10;
					if (i < width - 1)
					{
						floor[i + 1][j - 1] = 10;
					}
				}

				if (i < width - 1)
				{
					floor[i + 1][j] = 10;
					
					if (j < length - 1)
					{
						floor[i + 1][j + 1] = 10;
					}
				}
				if (j < length - 1)
				{
					floor[i][j + 1] = 10;
					if (i > 0)
					{
						floor[i - 1][j + 1] = 10;
					}
				}
				
				floor[i][j] = 10;
			}
		}
	}
	
	// dat robot vao ma tran, neu khong duoc thi phan hoi lai
	if (!robot.getInRoom(*this))
	{
		cout << "\n\tRobot khong the hut bui do phong qua nhieu do dac";
		cout << "\n\tVui long don dep lai phong de robot co the hut bui";
		return false;
	}
	else return true;
}

void Room::describe()
{
	printf("\n\t Giai thich cac ki hieu:");
	printf("\n\t _____");
	printf("\n\t|_____| : Da hut bui xong");
	printf("\n\t _____");
	printf("\n\t|__0__| : Chua duoc hut bui");
	printf("\n\t _____");
	printf("\n\t|/////| : Chuong ngai vat");
	printf("\n\t _____    _____    _____    _____");
	printf("\n\t|__^__|, |__v__|, |_>>>_|, |_<<<_| : Vi tri robot hien hanh");

	cout << "\n\n";
}

int Room::showFloor()
{
	int done = 1; // danh dau neu cong viec hoan tat => done == 1, nguoc lai done == 0
	
	// Ve vach ngan o tren cung
	cout << "\n\t";
	for (int j = 0; j < length; j++)
	{
		printf(" _____");
	}
	cout << endl;
	
	// Ve so do phong dua tren gia tri cac o trong ma tran	
	for (int i = 0; i < width; i++)
	{
		cout << "\t";
		for (int j = 0; j < length; j++)
		{
			if (j == 0)
			{
				printf("|"); // Dung vach ngan ben trai ma tran
			}

			if (floor[i][j] < 0) // la vi tri cua robot
			{
				if (floor[i][j] == -1)		// huong Bac
				{
					printf("__^__|");
				}
				else if (floor[i][j] == -2)	// huong Dong
				{
					printf("_>>>_|");
				}
				else if (floor[i][j] == -3)	// huong Tay
				{
					printf("_<<<_|");
				}
				else						// huong Nam
				{
					printf("__v__|");
				}
			}
			else // khong phai vi tri cua robot
			{
				if (floor[i][j] == 11)		// da di qua
				{
					printf("_____|");
				}
				else if (floor[i][j] == 10)	// chuong ngai vat
				{
					printf("/////|");
				}
				else						// 0 -> 9 la o chua hut bui
				{
					printf("__0__|");

					// Cong viec chua hoan tat => done = 0
					done = 0;
				}
			}
		}
		
		cout << endl;
	}

	return done; // phan hoi trang thai cong viec da hoan tat hay chua
}

int Room::valueAt(int i, int j)
{
	if (i < 0 || i >= width || j < 0 || j >= length)
		return 10;

	return floor[i][j];
}

void Room::setValue(int val, int i, int j)
{
	floor[i][j] = val;
}