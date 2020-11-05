#pragma once

class Stage
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	bool isDone; //게임이 끝났냐?
	bool isScral;
	bool isPlaying;
	int classType;

};