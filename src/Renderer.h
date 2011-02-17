#pragma once
#include "matrix.h"
#include <list>

class Object;
class Light;
class RenderableObject;

typedef std::list<Light*> LightList;
typedef LightList::iterator LightIterator;
typedef std::list<RenderableObject*> RenderList;
typedef RenderList::iterator RenderIterator;

class Renderer
{
public:
	Renderer();
	~Renderer();
	//If any error occured, return 0
	int initialize();
	void cleanup();

	//Call this after creating an object and setting its values
	void AddObject(RenderableObject* obj);
	void RemoveObject(RenderableObject* obj);
	void AddLight(Light* light);
	void RemoveLight(Light* light);

	//Called by Camera so it can change viewMatrix
	mat* ViewMatrix(){ return &viewMatrix; }

	void drawScene();

private:
	struct SDL_Surface* sdl_surface;

	int windowWidth, windowHeight;

	//When window is resized, generate a new projection  matrix
	void GenerateProjectionMatrix();
	mat projectionMatrix;
	mat viewMatrix;

	bool RemoveFromList(RenderableObject* obj, RenderList& renderlist);
	
	LightList lights;
	//Drawing in batches: for each shader there will be a seperate list with objects in it
	RenderList defaultObjects;
	//RenderList shadowcastObjects;
	//RenderList blurObjects;

	void DrawBatch(RenderList& objlist);
};
