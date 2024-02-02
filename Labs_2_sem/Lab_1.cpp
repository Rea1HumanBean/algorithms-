#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

struct Point {
	int x, y;
	Point(int _x, int _y) : x(_x), y(_y) {};
};

void sort_Insertion(std::vector<Point>& _arr) {
	for (int i = 0; i < _arr.size(); i++) {
		for (int j = i; j > 0 && _arr[j - 1].x > _arr[j].x; j--) {
			std::swap(_arr[j - 1], _arr[j]);
		}
	}
	for (int i = 0; i < _arr.size() - 1; i++) {
		if (_arr[i].x == _arr[i + 1].x && _arr[i].y > _arr[i + 1].y)
			std::swap(_arr[i], _arr[i + 1]);
	}
}

double calck_Angle(Point _a, Point _b, Point _c) { //Высчитываем угол между точками
	double angle_rad;

	double ux = _b.x - _a.x;
	double uy = _b.y - _a.y;
	double vx = _c.x - _b.x;
	double vy = _c.y - _b.y;

	double magnitudeU = sqrt(ux * ux + uy * uy);
	double magnitudeV = sqrt(vx * vx + vy * vy);

	if (magnitudeU > 0 && magnitudeV > 0) {
		double dotProduct = ux * vx + uy * vy;
		double cos_fi = dotProduct / (magnitudeU * magnitudeV);
		angle_rad = acos(cos_fi);
	}
	else
		angle_rad = 0.0;

	int angle_deg = 180 - angle_rad * 180.0 / 3.1415;

	return angle_deg;
};

int orientation(Point p, Point q, Point r) {//определаю направление вектора 
	int pseudo_cross_product = (q.x - p.x) * (r.y - q.y) - (r.x - q.x) * (q.y - p.y);

	if (pseudo_cross_product > 0) {
		return 1;  //Поворот против часовой стрелке
	}
	else if (pseudo_cross_product < 0) {
		return -1; // Поворот g часовой стрелке
	}
	else {
		return 0; // Векторы коллинеарны
	}
}

void chain(std::stack<Point>& Shell, std::vector<Point>& _arr, int _a, int _b) {
	int i = 0, angl = 0;

	for (int j = 0; j < _arr.size(); j++) {
		int _angl = calck_Angle(_arr[_a], _arr[_b], _arr[j]);
		if ((orientation(_arr[_a], _arr[_b], _arr[j]) > 0) && _angl > angl) {
			angl = _angl;
			i = j;
		}
	}

	std::cout << angl << '-' << i << std::endl;
	if (i != 0) {
		Shell.push(_arr[i]);
		chain(Shell, _arr, _b, i);
	}
};


std::stack<Point> build_Shell(std::vector<Point>& _arr) {
	std::stack<Point> Shell;
	Shell.push(_arr[0]);
	int pos_f = _arr.size() - 1;
	chain(Shell, _arr, pos_f, 0);
	return Shell;
};


int main() {
	std::vector<Point> PointArray = { {3,3}, {2,-4}, {0,0}, {4,2}, {6,1}, {2,5}, {7,5}, {10,0}, {0,2} };
	sort_Insertion(PointArray);

	std::stack<Point> Shell = build_Shell(PointArray);
	if(Shell.size() > 2){
		std::cout<< "Shell created"<<std::endl;
		for(int i = 0; i < Shell.size();i++)
			std::cout << Shell[i].x <<' '<<Shell[i].y<<std::endl;
	}

	return 0;
}