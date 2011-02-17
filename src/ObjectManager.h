#pragma once
#include <list>

class Camera;
class Object;
class Renderer;

class ObjectManager
{
public:
	ObjectManager(Renderer* renderer);
	~ObjectManager();
	
	//If any error occured, return 0
	int initialize();
	void cleanup();


	void Update(float ElapsedTime);

	//In the future ObjectManager will be the one that
	//creates an object, looks in xml files to see
	//what meshes it needs and requests those from Meshmanager
	//For now we just have this function ;)
	void LoadSomeObjects();

private:
	Renderer* const mRenderer;

	Camera* camera;

	//Only available for constructor of Object class
	friend Object;
	//Note: because these functions are called from the constructor, the
	//objects will not be initalized yet: their member variables can not
	//be accessed yet.
	void registerObject(Object* object);
	void unregisterObject(Object* object);

	typedef std::list<Object*> ObjectContainer;
	typedef ObjectContainer::iterator ObjectIterator;
	ObjectContainer	mObjects;
};

