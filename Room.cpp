#include "Room.h"

Room::Room(int x, int y)
{
	width = x;
	length = y;

	initializeGrid(); // randomly initialize a matrix
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
	
	floor = new int*[width];
	
	srand(time(NULL));
	for (int i = 0; i < width; i++) 
	{
		floor[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			floor[i][j] = rand() % 10; // assign value in range [0, 9] to the elements
		}
	}
}

bool Room::initializeRoom(Robot& robot)
{
	// create the obstacle in the room
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
	
	// put the Robot into the matrix, then return the outcome
	if (!robot.getInRoom(*this))
	{
		cout << "\n\tCleaning cannot be started, there are to many furniture in the room";
		cout << "\n\tPlease tidy up the room first";
		return false;
	}
	else return true;
}

void Room::describe()
{
	printf("\n\t Symbols definition:");
	printf("\n\t _____");
	printf("\n\t|_____| : Cleaned position");
	printf("\n\t _____");
	printf("\n\t|__0__| : Uncleaned position");
	printf("\n\t _____");
	printf("\n\t|/////| : Obstable");
	printf("\n\t _____    _____    _____    _____");
	printf("\n\t|__^__|, |__v__|, |_>>>_|, |_<<<_| : Robot position");

	cout << "\n\n";
}

int Room::showFloor()
{
	int done = 1; // if cleaning is done => done == 1, else done == 0
	
	// Create the top wall
	cout << "\n\t";
	for (int j = 0; j < length; j++)
	{
		printf(" _____");
	}
	cout << endl;
	
	// Create the room chart, based on the values in the matrix	
	for (int i = 0; i < width; i++)
	{
		cout << "\t";
		for (int j = 0; j < length; j++)
		{
			if (j == 0)
			{
				printf("|"); // Create the left wall
			}

			if (floor[i][j] < 0) // if Robot is in this position
			{
				if (floor[i][j] == -1)		// North
				{
					printf("__^__|");
				}
				else if (floor[i][j] == -2)	// East
				{
					printf("_>>>_|");
				}
				else if (floor[i][j] == -3)	// West
				{
					printf("_<<<_|");
				}
				else						// South
				{
					printf("__v__|");
				}
			}
			else // if Robot is not in this position
			{
				if (floor[i][j] == 11)		// cleaned
				{
					printf("_____|");
				}
				else if (floor[i][j] == 10)	// obstacle
				{
					printf("/////|");
				}
				else						// 0 -> 9 => uncleaned
				{
					printf("__0__|");

					// Cleaning is not done yet => done = 0
					done = 0;
				}
			}
		}
		
		cout << endl;
	}

	return done; // return the progress of the job
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