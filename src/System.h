#pragma once

//Forward declarations so we dont have to include headers
class Renderer;
class ObjectManager;
class Game;
class InputHandler;
class Network;

class System
{
public:
	System();
	~System();

	//If any error occured, return 0
	int initialize();
	void cleanup();

	void gameLoop();

private:
	Renderer*		const mRenderer;
	ObjectManager*	const mObjectMgr;
	Game*			const mGame;
	InputHandler*	const mInputHandler;
	Network*		const mNetwork;
	//TODO: UI / Interface class here (not in renderer)

	//High precision timer. For now only implemented on WIN32 and MAC.
	void initializeTimer();
	float GetElapsedTime(); //Time in seconds since last call
#ifdef _WIN32
	float Frequency;
	__int64 CurrentTime;
#endif
#ifdef __APPLE__
    uint64_t start, end;
#endif
};
