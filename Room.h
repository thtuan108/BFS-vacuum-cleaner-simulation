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
	// floor la ma tran 2 chieu luu cac o trong phong
	// Gia tri moi o trong ma tran tuong ung voi hinh anh hien thi
	// -1     : Vi tri robot hien tai huong ve phia Bac
	// -2     : Vi tri robot hien tai huong ve phia Dong
	// -3     : Vi tri robot hien tai huong ve phia Tay
	// -4     : Vi tri robot hien tai huong ve phia Nam
	// 0 -> 9 : Vi tri robot chua di qua
	// 10     : Vi tri co chuong ngai vat
	// 11     : Vi tri robot da di qua

	int width;		// chieu rong
	int length;		// chieu dai

public:
	Room() {};
	Room(int, int);

	int getWidth();
	int getLength();
	int valueAt(int, int);			// truy xuat gia tri tai 1 o tren floor
	void setValue(int, int, int);	// dat gia tri cho 1 o tren floor

	void initializeGrid();			// khoi tao ma tran voi cac gia tri ngau nhien
	bool initializeRoom(Robot&);	// tao cac chuong ngai vat hinh khoi, tra ve "true" neu thanh cong
	void describe();				// giai thich cac ki hieu tren ma tran
	int showFloor();				// in ra trang thai hien tai cua ma tran, tra ve 1 neu da don xong
};

