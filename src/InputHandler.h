#pragma once
#include "SDL/SDL_keysym.h" //The key constants

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	//If any error occured, return 0
	int initialize(){ return 1; }
	void cleanup(){ return; }

	//Called by System	
    void KeyDown(SDLKey key, bool Down);
    void MouseDown(int button, bool Down, int x, int y);
    void MouseMoved(int x, int y);

private:
	//mouse state
	int MouseX, MouseY;
	bool MouseDrag;
};

