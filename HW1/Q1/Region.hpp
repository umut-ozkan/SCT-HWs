#ifndef REGION_HPP
#define REGION_HPP

#include <iostream>
#include <cmath>

struct Point {
    float x;
    float y;
    float z;
Point(float x, float y, float z) : x(x), y(y), z(z) {}
};

enum Region {
    INVALID_REGION = -1,
    ORIGIN,
    REGION_1,
    REGION_2,
    REGION_3,
    REGION_4,
    REGION_5,
    REGION_6,
    REGION_7,
    REGION_8
};



float distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

float zero_distance(Point p) {
    return distance(p, Point(0., 0., 0.));
}


static bool compare(Point p1, Point p2) {
    return zero_distance(p1) > zero_distance(p2) ? true : false;
}

int region(Point p){
    if (p.x == 0 && p.y == 0 && p.z == 0)
        return ORIGIN;
    else if (p.x > 0 && p.y > 0 && p.z > 0)
        return REGION_1;
    else if (p.x < 0 && p.y > 0 && p.z > 0)
        return REGION_2;
    else if (p.x < 0 && p.y < 0 && p.z > 0)
        return REGION_3;
    else if (p.x > 0 && p.y < 0 && p.z > 0)
        return REGION_4;
    else if (p.x > 0 && p.y > 0 && p.z < 0)
        return REGION_5;
    else if (p.x < 0 && p.y > 0 && p.z < 0)
        return REGION_6;
    else if (p.x < 0 && p.y < 0 && p.z < 0)
        return REGION_7;
    else if (p.x > 0 && p.y < 0 && p.z < 0)
        return REGION_8;
    else
        return INVALID_REGION; // If it is in the line but not in the origin
}

bool is_in_same_region(Point p1, Point p2){
    if(region(p1) == region(p2))
        return true;
    return false;
}

#endif // REGION_HPP


