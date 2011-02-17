#include "Object.h"
#include "ObjectManager.h"

Object::Object(ObjectManager* objectmgr) : mObjMgr(objectmgr), position(0.0f), movement(0.0f), yaw(0.0f), pitch(0.0f), roll(0.0f) {
	mObjMgr->registerObject(this);
}

Object::~Object(){
	mObjMgr->unregisterObject(this);
}

void Object::Update(float ElapsedTime){
	position += movement * ElapsedTime;
	return;
}