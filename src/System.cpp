#include "System.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "Network.h"

#include "SDL/SDL.h"

System::System() :
	mRenderer(new Renderer),
	mInputHandler(new InputHandler),
	mNetwork(new Network),
	mObjectMgr(new ObjectManager(mRenderer)),
	mGame(new Game)
{
}

System::~System(){
	delete mGame;
	delete mObjectMgr;
	delete mNetwork;
	delete mInputHandler;
	delete mRenderer;
}

int System::initialize(){
	//Initialize SDL
	if( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 ) return 0;
	initializeTimer();
	if( !mRenderer->initialize() ) return 0;
	if( !mInputHandler->initialize() ) return 0;
	if( !mNetwork->initialize() ) return 0;
	if( !mObjectMgr->initialize() ) return 0;
	if( !mGame->initialize() ) return 0;

	//Temporary
	mObjectMgr->LoadSomeObjects();

	return 1;
}

void System::cleanup(){
	mGame->cleanup();
	mObjectMgr->cleanup();
	mNetwork->cleanup();
	mInputHandler->cleanup();
	mRenderer->cleanup();
	//Cleanup SDL
	SDL_Quit();
}


void System::gameLoop(){
    SDL_Event Event;
	bool running = true;
    while(running) {
        while(SDL_PollEvent(&Event)) {
			switch( Event.type ){
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				mInputHandler->KeyDown( Event.key.keysym.sym , Event.key.state == SDL_PRESSED );
				break;
			case SDL_MOUSEMOTION:
				mInputHandler->MouseMoved( Event.motion.x, Event.motion.y );
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				mInputHandler->MouseDown( Event.button.button, Event.button.state == SDL_PRESSED, Event.button.x, Event.button.y );
				break;
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
        }
		mObjectMgr->Update(GetElapsedTime());
		mRenderer->drawScene();
    }
	return;
}
