#pragma once
#include "Vector3.h"

class ObjectManager;

//Note: this class is the base class of all objects: lights, cameras, players, etc
//It should not have to be more than position, orientation and movement.
//If an object needs other stuff it should probably be in a subclass.
//Object is automatically added to ObjectManager and its Update method
//is called every frame.

//Important: every subclass the constructor should set the variables in such a way
//that the Update() function will not crash if it would be called right after the constructor.
//So if you don't initialize a pointer in your constructor and then use the pointer
//in Update() then it might crash because as soon as the constructor is done the object
//is in the object list and Update() can be called.

class Object
{
public:
	Object(ObjectManager* objectmgr);
	virtual ~Object(void);

	virtual void Update(float ElapsedTime);

	Vector3 position;
	Vector3 movement; //The current movement direction. The length of this vector is the speed in units per second
	float yaw, pitch, roll; //The angle of the object, does not have to be move direction

protected:
	ObjectManager* const mObjMgr;
};
