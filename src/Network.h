#pragma once

class Network
{
public:
	Network();
	~Network();

	//If any error occured, return 0
	int initialize(){ return 1; }
	void cleanup(){ return; }
};

