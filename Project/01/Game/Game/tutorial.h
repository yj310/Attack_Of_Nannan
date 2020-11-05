#pragma once
#include "stage.h"

class Tutorial : public Stage
{
public:
	Tutorial();
	void Update() override;
	void Render() override;

	int currentPage;
};