#ifndef _POINT_H
#define _POINT_H
#include<iostream>
using namespace std;

class Point {
public:
    int x;
    int y;
    Point& operator =(const Point & operandeDroite);
};

#endif
