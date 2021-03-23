#ifndef _POINT_H
#define _POINT_H
#include<iostream>
using namespace std;

class Point {
public:
    int x;
    int y;

    Point();
    Point(int valX, int valY);
    Point& operator =(const Point & operandeDroite);
};

#endif
