#include "stdafx.h"
#include "JSONObject.h"


JSONObject::JSONObject()
{
}


JSONObject::~JSONObject()
{
}

void JSONObject::setParent(JSONObject* jsonObject)
{
	this->parent = jsonObject;
}

JSONObject* JSONObject::getParent()
{
	return this->parent;
}
