#pragma once

class InputManager
{
public:
	char keyBuffer[256];
	char prevKeyBuffer[256];

	void Update()
	{
		for (int i = 0; i < 256; ++i)
		{
			prevKeyBuffer[i] = keyBuffer[i];
		}
	}
};