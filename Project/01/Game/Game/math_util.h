#pragma once

bool isCircleCollided(float ax, float ay, float ar, float bx, float by, float br);
bool isBoxCollided(float ax, float ay, float awidth, float aheight,
	float bx, float by, float bwidth, float bheight);
bool isCircleVsBoxCollided(float ax, float ay, float ar,
	float bx, float by, float bw, float bh);