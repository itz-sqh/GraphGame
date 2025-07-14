#include"Game.h"
#include<iostream>

int main()
{
    CircleObject circle1({1, 8}, 5);
    CircleObject circle2({-5, 6}, 3);
    Line line(12 ,4, 12);
    auto points = circleIntersection(circle1, circle2);
    for (const auto& point : points) {
        std::cout<< point.x << " " << point.y << std::endl;
    }
}
