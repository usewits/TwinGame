#pragma once
#include "object.h"

class RenderableObject : public Object {
public:
	RenderableObject(ObjectManager* objectmgr);
	virtual ~RenderableObject();

	bool visible;
};

