#pragma once

class Stage
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	bool isDone; //������ ������?
	bool isScral;
	bool isPlaying;
	int classType;

};