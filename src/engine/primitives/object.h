#pragma once

// TODO: Call init() in constructor
class Object {
public:
	virtual void move(float x, float y, float z) = 0;
	virtual void scale(float x, float y, float z) = 0;
	virtual void rotateX(float angle) = 0;
	virtual void rotateY(float angle) = 0;
	virtual void rotateZ(float angle) = 0;
	virtual void draw() = 0;
};