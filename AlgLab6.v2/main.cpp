#include<iostream>
#include<cstdlib>
#include<ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;
// �������� ������������ ��������� 

const int wall = -1, pass = -2, blank = -2;

// ��������������� �������, ���������� ������
bool deadend(int x, int y, const vector<vector<int>>& maze, int height, int width) {
	int a = 0;

	if (x != 1) {
		if (maze[y][x - 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != 1) {
		if (maze[y - 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (x != width - 2) {
		if (maze[y][x + 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != height - 2) {
		if (maze[y + 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (a == 4)
		return 1;
	else
		return 0;
}

// ����������� ���������� � ������� ���������� �������
void visual(vector<vector<int>>& maze, int height, int width) {
	int ex = width - 1, ey = height - 2;
	int	x = 0, y = 1;
	maze[y][x] = pass;
	maze[ey][ex] = pass;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			switch (maze[i][j]) {
			case wall: cout << "0 "; break;
			case pass: cout << "  "; break;
			}
		cout << endl;
	}
	//cout << endl;
	//cout << " ==============="<<endl;

	//for (int i = 0; i < height; i++) 
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		cout << maze[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	maze[y][x] = wall;
	//maze[ey][ex] = wall;
}


// ���������� ��������
void mazemake(vector<vector<int>>& maze, int height, int width) {
	int x, y, c, a;
	int ex, ey;
	bool b;

	for (int i = 0; i < height; i++) // ������ ����������� ������-��������
		for (int j = 0; j < width; j++)
			maze[i][j] = wall;

	x = 1; y = 1; a = 0; // ����� ����������� ����� � �������


	while (a < 10000) { // ��, ��������, �������, ����� ���� ���, �� ����
		maze[y][x] = pass; a++;
		//	maze[ey][ex] = pass; a++;
		while (1) { // ����������� ����, ������� ����������� ������ �������
			c = rand() % 4; // ���������, ��� ���� ���������
			switch (c) {  // �� ��� ������ � ����� ����������� �� ������
			case 0: if (y != 1)
				if (maze[y - 2][x] == wall) { // �����
					maze[y - 1][x] = pass;
					maze[y - 2][x] = pass;
					y -= 2;
				}
			case 1: if (y != height - 2)
				if (maze[y + 2][x] == wall) { // ����
					maze[y + 1][x] = pass;
					maze[y + 2][x] = pass;
					y += 2;
				}
			case 2: if (x != 1)
				if (maze[y][x - 2] == wall) { // ������
					maze[y][x - 1] = pass;
					maze[y][x - 2] = pass;
					x -= 2;
				}
			case 3: if (x != width - 2)
				if (maze[y][x + 2] == wall) { // �������
					maze[y][x + 1] = pass;
					maze[y][x + 2] = pass;
					x += 2;
				}
			}
			if (deadend(x, y, maze, height, width))
				break;
		}

		if (deadend(x, y, maze, height, width)) // ����������� ����� �� ������
			do {
				x = 2 * (rand() % ((width - 1) / 2)) + 1;
				y = 2 * (rand() % ((height - 1) / 2)) + 1;
			} while (maze[y][x] != pass);
	} // �� ���� � ���.

}


bool Wave(const vector<vector<int>>& maze, int ax, int ay, int bx, int by, int height, int width)
{
	int len;

	vector<vector<int> > grid(width, vector<int>(height));
	grid = maze;

	vector<int> px(height * width);
	vector<int> py(height * width);
	int dx[4] = { 1, 0, -1, 0 };   // ��������, ��������������� ������� ������
	int dy[4] = { 0, 1, 0, -1 };   // ������, �����, ����� � ������
	int d, x, y, k;
	bool stop;

	if (grid[ay][ax] == -1 || grid[by][bx] == -1) return false;  // ������ (ax, ay) ��� (bx, by) - �����

	// ��������������� �����
	d = 0;
	grid[ay][ax] = 0;            // ��������� ������ �������� 0
	do {
		stop = true;               // ������������, ��� ��� ��������� ������ ��� ��������
		for (y = 0; y < height; ++y)
			for (x = 0; x < width; ++x)
				if (grid[y][x] == d)                         // ������ (x, y) �������� ������ d
				{
					for (k = 0; k < 4; ++k)                    // �������� �� ���� ������������ �������
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < height && ix >= 0 && ix < width && grid[iy][ix] == -2)
						{
							stop = false;              // ������� ������������ ������
							grid[iy][ix] = d + 1;      // �������������� �����
						}
					}
				}
		d++;
	} while (!stop && grid[by][bx] == -2);

	if (grid[by][bx] == -2) return false;  // ���� �� ������


	// �������������� ����
	len = grid[by][bx];            // ����� ����������� ���� �� (ax, ay) � (bx, by)
	cout << "Min len=" << len + 2 << endl;
	cout << "--------------------------------------" << endl;
	grid[height-2][width-1] = -1;
	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++)
	//	{
	//	cout << grid[i][j] << "\t";
	//	}
	//cout << endl;
	//}
	// 
	//x = bx;
	//y = by;
	//d = len+2;
	//while (d > 0)
	//{
	//	px[d] = x;
	//	py[d] = y;                   // ���������� ������ (x, y) � ����
	//	d--;
	//	for (k = 0; k < 4; ++k)
	//	{
	//		int iy = y + dy[k], ix = x + dx[k];
	//		if (iy >= 0 && iy < height && ix >= 0 && ix < width && grid[iy][ix] == d)
	//		{
	//			x = x + dx[k];
	//			y = y + dy[k];           // ��������� � ������, ������� �� 1 ����� � ������
	//			break;
	//		}
	//	}
	//}
	//px[0] = ax;
	//py[0] = ay;
	//// ������ px[0..len] � py[0..len] - ���������� ����� ����
	//cout << "--------------------------------------" << endl;
	return true;

}

bool prover(vector<vector<int>>& grid, int x, int y)
{
	int k=0;
	if (grid[x - 1][y] == -1) { k += 1; }
	if (grid[x][y - 1] == -1) { k += 1; }
	if (grid[x + 1][y] == -1) { k += 1; }
	if (grid[x][y + 1] == -1) { k += 1; }
	if (k > 2) return true;
	else return false;
}
void stroit(vector<vector<int>>& grid,int x,int y)
{
	int i = 1;
	while (i == 1) {
		if (grid[x - 1][y] != -1  && prover(grid, x-1, y) == true) { grid[x - 1][y] = -1; x = x - 1;}
		else if (grid[x][y - 1] != -1 && prover(grid, x , y-1) == true) { grid[x][y - 1] = -1; y = y - 1; }
		else if (grid[x + 1][y] != -1 && prover(grid, x +1, y) == true) { grid[x + 1][y] = -1; x = x + 1; }
		else if (grid[x][y + 1] != -1 && prover(grid, x , y+1) == true) { grid[x][y + 1] = -1; y = y + 1; }
		else i = 0;
	}
}


void block(vector<vector<int>>& grid, int lx, int ly, int bx, int by, int height, int width)
{
	int k = 0;
	grid[lx][ly] = 0;
	for (int y = height - 2; y >= 1; y--)
		for (int x = width - 2; x >= 1; x--)
		{
			if ((grid[x][y] == -2) && (x != 0) && (y != 0) && (x != height - 1) && (y != height - 1))
			{
				if (grid[x - 1][y] == -1) { k += 1; }
				if (grid[x][y - 1] == -1) { k += 1; }
				if (grid[x + 1][y] == -1) { k += 1; }
				if (grid[x][y + 1] == -1) { k += 1; }
			}

			if (k == 3)
			{
				grid[x][y] = -1;
				stroit(grid, x, y);
				/*	cout << "==================" << endl;
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							cout << grid[i][j] << "\t";
						}
						cout << endl;
					}*/
			}
			k = 0;
		}
	grid[lx][ly] = pass;
  cout << "yes" << endl;
	//visual(grid, height, width);

}

int main() {
	ofstream out;
	out.open("D:\\Visual Studio codes\\algoritm.laba.6\\result2.txt");

	srand((unsigned)time(NULL));
	//int End =180;

	//for(int n = 9; n < End;) 
	//{
		int n = 109;
		int height = n, width = n;
		vector<vector<int> > maze(width, vector<int>(height));
		mazemake(maze, height, width);
		visual(maze, height, width);
		int ex = (width - 2), ey = (height - 2);
		int x = 1, y = 1;
		vector<vector<int> > grid(width, vector<int>(height));
		grid = maze;


		auto start = chrono::high_resolution_clock::now();
		Wave(grid, x, y, ex, ey, height, width);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = end - start;

		start = chrono::high_resolution_clock::now();
		block(maze, x, y, ex, ey, height, width);
		end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration2 = end - start;
		out << n << "\t" << duration.count() << "\t" << duration2.count() << endl;
		cout << "KekW for " << n << " Ready " << endl;
		cout << "==============================================" << endl;
		n += 10;
	//}

	return 0;
}