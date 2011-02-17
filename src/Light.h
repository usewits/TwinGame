#pragma once
#include "Object.h"

class Light : public Object {
public:
	Light(ObjectManager* objectmgr);
	virtual ~Light(void);

	//Light color and light type
};

