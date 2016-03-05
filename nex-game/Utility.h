#pragma once

#include "stdafx.h"


/*
	Print function compatible with the renderer
*/
void print(unsigned int line, const char* fmt, ...);

/*
	Distance between 2 points in 3D space
*/
float Distance(float x1, float y1, float z1, float x2, float y2, float z2);

/*
	Distance between 2 points in 2D space
*/
float Distance2D(float x1, float y1, float x2, float y2);

/*
	Distance from any point on a projected line to a point
*/
double GetDistancePointLine(float line_x,float line_y,float line_z,float vector_x,float vector_y,float vector_z,float point_x,float point_y,float point_z);

/*
	Angle from point to dest
*/
float GetAngleToPoint(float fPointX, float fPointY, float fDestX, float fDestY);

/*
	2D Projection position based on distance and angle
*/
void GetXYFromAngle(float &x, float &y, float a, float distance);

/*
	3D Projection position based on distance and angles
*/
void GetXYZFromAngle(float &x, float &y, float &z, float angle, float elevation, float distance);


/*
	Checks if one angle is within another angle
*/
bool AngleInRangeOfAngle(float a1, float a2, float range);


/*
	Returns the absolute value of an angle
*/
float absoluteangle(float angle);


/*
	Checks if a variable is not a number
	Credits - Y_Less (http://forum.sa-mp.com/showthread.php?t=57018)
*/
bool IsNaN(float number);
