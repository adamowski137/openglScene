#define STB_IMAGE_IMPLEMENTATION
#include "Window.hpp"

int main()
{
	int width = 1260;
	int height = 768;
	Window::getInstance(width, height).runWindow();
}