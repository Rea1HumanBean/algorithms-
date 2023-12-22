#include <iostream>
#include <cmath>

struct Point {
    double x, y;
};

// Функция для вычисления расстояния между двумя точками
double distance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Функция для проверки вложенности точек в окружности
bool isInsideCircle(const Point& center, double radius, const Point& p) {
    return distance(center, p) <= radius;
}

// Функция для проверки пересечения двух окружностей
bool circlesIntersect(const Point& center1, double radius1, const Point& center2, double radius2) {
    return distance(center1, center2) < (radius1 + radius2);
}

// Функция для проверки вложенности точек в треугольник
bool isInsideTriangle(const Point& p1, const Point& p2, const Point& p3, const Point& p) {
    double d1 = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
    double d2 = (p.x - p2.x) * (p3.y - p2.y) - (p.y - p2.y) * (p3.x - p2.x);
    double d3 = (p.x - p3.x) * (p1.y - p3.y) - (p.y - p3.y) * (p1.x - p3.x);

    return ((d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0));
}

int main() {
    // Задаем 9 точек
    Point points[9];
    for (int i = 0; i < 9; ++i) {
        std::cout << "Введите координаты точки " << i + 1 << " (x y): ";
        std::cin >> points[i].x >> points[i].y;
    }

    // Проверяем, можно ли построить систему из двух окружностей и треугольника
    if (points[0].x == points[1].x && points[0].y == points[1].y) {
        std::cerr << "Ошибка: Точки 1 и 2 совпадают." << std::endl;
        return 1;
    }

    Point center1 = points[0];
    double radius1 = distance(points[0], points[1]) / 2;

    Point center2 = points[2];
    double radius2 = distance(points[2], points[3]) / 2;

    if (circlesIntersect(center1, radius1, center2, radius2)) {
        std::cerr << "Ошибка: Окружности пересекаются." << std::endl;
        return 1;
    }

    Point triangle1 = points[4];
    Point triangle2 = points[5];
    Point triangle3 = points[6];

    if (!isInsideCircle(center1, radius1, triangle1) || !isInsideCircle(center1, radius1, triangle2) || !isInsideCircle(center1, radius1, triangle3)) {
        std::cerr << "Ошибка: Треугольник не вложен в первую окружность." << std::endl;
        return 1;
    }

    if (!isInsideCircle(center2, radius2, triangle1) || !isInsideCircle(center2, radius2, triangle2) || !isInsideCircle(center2, radius2, triangle3)) {
        std::cerr << "Ошибка: Треугольник не вложен во вторую окружность." << std::endl;
        return 1;
    }

    if (isInsideTriangle(triangle1, triangle2, triangle3, center1) || isInsideTriangle(triangle1, triangle2, triangle3, center2)) {
        std::cerr << "Ошибка: Треугольник вложен в одну из окружностей." << std::endl;
        return 1;
    }

    std::cout << "Возможно построить систему из двух окружностей и треугольника." << std::endl;

    return 0;
}