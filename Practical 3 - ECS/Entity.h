#pragma once
#include <vector>
#include <map>
#include "Component.h"

class Entity
{
	int id;
public:
	Entity() {};
	void addComponent(std::string name, Component& c) { components[name] = &c; }
	void removeComponent(std::string& name) { components.erase(name); }
	Component& getComponent(std::string name) { return *components[name]; }
private:
	std::map<std::string, Component*> components;
};