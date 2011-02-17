#pragma once

class Game
{
public:
	Game(void);
	~Game(void);

	//If any error occured, return 0
	int initialize(){ return 1; }
	void cleanup(){ return; }
};

