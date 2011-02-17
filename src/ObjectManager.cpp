#include "ObjectManager.h"
#include "Renderer.h"
#include "Object.h"
#include "Camera.h"

ObjectManager::ObjectManager(Renderer* renderer) : mRenderer(renderer), mObjects() {
	//Watch out! When creating the camera object
	//it will add itself to ObjectManager through
	//registerObject(). However, we are still
	//in the constructor of ObjectManager so
	//the object list might not even be valid yet.
	//In this case it will work because mObjects
	//is initialized in the initialisation list
	//above. Just pay attention with any changes.
	camera = new Camera(this);
}


ObjectManager::~ObjectManager(){
	delete camera;
}

int ObjectManager::initialize(){
	camera->viewMatrix = mRenderer->ViewMatrix();
	//TODO: Initialize MeshManager and TextureManager
	return 1;
}

void ObjectManager::cleanup(){
	//Delete all objects
	//When calling delete, the deconstructor will be called which will
	//in turn call unregisterObject which will remove it from mObjects
	while( !mObjects.empty() ) delete mObjects.back();
}

//Note: because these functions are called from the constructor, the objects
//will not be initalized yet: their member variables can not be accessed yet.
void ObjectManager::registerObject(Object* object){
	mObjects.push_back(object);
}

void ObjectManager::unregisterObject(Object* object){
	for( ObjectIterator obj = mObjects.begin(); obj != mObjects.end(); ++obj ){
		if( *obj == object ){
			mObjects.erase(obj);
			break;
		}
	}
}

void ObjectManager::Update(float ElapsedTime){
	for( ObjectIterator obj = mObjects.begin(); obj != mObjects.end(); ++obj ){
		(*obj)->Update(ElapsedTime);
	}
}

void ObjectManager::LoadSomeObjects(){

}