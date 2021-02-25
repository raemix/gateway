#pragma once
#include <iostream>

struct Vector2{
	Vector2():x(0.0f),y(0.0f){}
	Vector2(float x, float y):x(x),y(y){}
	void print(){std::cout << x << ", " << y << std::endl;}
	float x,y;
};