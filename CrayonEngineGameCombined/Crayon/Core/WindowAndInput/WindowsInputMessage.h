#pragma once
#include<Windows.h>
struct WindowsInputMessage
{
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
};