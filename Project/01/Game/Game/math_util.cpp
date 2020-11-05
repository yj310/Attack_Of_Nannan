#include "stdafx.h"

#include "math_util.h"
#include <cmath>

// circle vs circle
bool isCircleCollided(float ax, float ay, float ar,
	float bx, float by, float br)
{
	const float dx = bx - ax;
	const float dy = by - ay;
	const float d = sqrt(dx * dx + dy * dy);

	if (ar + br < d)
	{
		return false;
	}

	return true;
}

// box vs box
bool isBoxCollided(float ax, float ay, float awidth, float aheight,
	float bx, float by, float bwidth, float bheight)
{
	bool xAxis = false;
	bool yAxis = false;

	// x axis
	if (ax + awidth > bx&& bx + bwidth > ax)
		xAxis = true;

	// y axis
	if (ay + aheight > by&& by + bheight > ay)
		yAxis = true;

	if (xAxis && yAxis)
		return true;

	return false;
}

// circle vs box
bool isCircleVsBoxCollided(float ax, float ay, float ar,
	float bx, float by, float bw, float bh)
{
	float halfW = bw / 2;
	float halfH = bh / 2;

	float distX = abs(ax - bx + halfW);
	float distY = abs(ay - by + halfH);

	if (distX > halfW + ar) return false;
	if (distY > halfH + ar) return false;

	if (distX < halfW) return true;
	if (distY < halfH) return true;

	float dx = distX - halfW;
	float dy = distY - halfH;

	return (dx * dx + dy * dy) <= (ar * ar);
}