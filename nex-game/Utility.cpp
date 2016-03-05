/*
*/

#include "stdafx.h"

#include <math.h>
#include <cstdarg>
#include <cstdio>
#include <windows.h>


#include "Utility.h"


void print(unsigned int line, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	COORD p = { 0, (int)line };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);

	vprintf(fmt, args);
	printf("\n");

	va_end(args);
}

/*
	Distance between 2 points in 3D space
*/
float Distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return sqrt((((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2))));
}

/*
	Distance between 2 points in 2D space
*/
float Distance2D(float x1, float y1, float x2, float y2)
{
	return sqrt( ((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)) );
}

/*
	Distance from any point on a projected line to a point
*/
double GetDistancePointLine(float line_x,float line_y,float line_z,float vector_x,float vector_y,float vector_z,float point_x,float point_y,float point_z)
{
	return sqrt(pow((vector_y) * ((point_z) - (line_z)) - (vector_z) * ((point_y) - (line_y)), 2.0)+pow((vector_z) * ((point_x) - (line_x)) - (vector_x) * ((point_z) - (line_z)), 2.0)+pow((vector_x) * ((point_y) - (line_y)) - (vector_y) * ((point_x) - (line_x)), 2.0))/sqrt((vector_x) * (vector_x) + (vector_y) * (vector_y) + (vector_z) * (vector_z));
}

/*
	Angle from point to dest
*/
float GetAngleToPoint(float fPointX, float fPointY, float fDestX, float fDestY)
{
	return absoluteangle(-(90-(atan2((fDestY - fPointY), (fDestX - fPointX)))));
}

/*
	2D Projection position based on distance and angle
*/
void GetXYFromAngle(float &x, float &y, float a, float distance)
{
	x+=(distance*sin(-a)),y+=(distance*cos(-a));
}

/*
	3D Projection position based on distance and angles
*/
void GetXYZFromAngle(float &x, float &y, float &z, float angle, float elevation, float distance)
{
    x += ( distance*sin(angle)*cos(elevation) ),y += ( distance*cos(angle)*cos(elevation) ),z += ( distance*sin(elevation) );
}


/*
	Checks if one angle is within another angle
*/
bool AngleInRangeOfAngle(float a1, float a2, float range)
{
	a1 -= a2;
	if((a1 < range) && (a1 > -range)) return true;

	return false;
}


/*
	Returns the absolute value of an angle
*/
float absoluteangle(float angle)
{
	while(angle < 0.0)angle += 360.0;
	while(angle > 360.0)angle -= 360.0;
	return angle;
}


/*
	Checks if a variable is not a number
	Credits - Y_Less (http://forum.sa-mp.com/showthread.php?t=57018)
*/
bool IsNaN(float number)
{
    return !(number <= 0 || number > 0);
}
