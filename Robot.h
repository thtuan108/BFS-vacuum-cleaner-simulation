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
	// Toa do vi tri cua robot trong phong:
	int x;	// toa do theo chieu rong
	int y;	// toa do theo chieu dai
	Direction direction;	// huong di chuyen hien tai
	int step;				// danh dau so buoc ma robot da di

	string brand;		// Nhan hieu robot
	string productCode;	// Ma so san pham

	int toNorth(Room&);		// ve huong Bac, tra ve 1 neu da don dep xong
	int toEast(Room&);		// ve huong Dong, tra ve 1 neu da don dep xong
	int toWest(Room&);		// ve huong Tay, tra ve 1 neu da don dep xong
	int toSouth(Room&);		// ve huong Nam, tra ve 1 neu da don dep xong

	int batteryWarning();			// bao pin yeu duoi 15% va tuy chon sac pin
	vector<int> findRoute(Room&);	// tim duong den o chua duoc don dep gan nhat
	int move(Room&, vector<int>);	// di chuyen theo lo trinh duoc cung cap

public:
	Robot();

	int getX();
	int getY();

	void showInfor();		// hien thi thong tin cua robot
	bool getInRoom(Room&);	// dat robot vao phong (ma tran), huong Bac, tra ve "true" neu thanh cong

	void run(Room&);
};