#pragma once
#include <vector>
#include <map>
#include "Component.h"

class Entity
{
public:
	Entity(std::string name) : m_name(name), m_alive(true) {};
	void addComponent(std::string name, Component& c) { components[name] = &c; }
	void removeComponent(std::string& name) { components.erase(name); }
	Component& getComponent(std::string name) { return *components[name]; }
	std::string& getName() { return m_name; }
	bool& getAlive() { return m_alive; }
	void setAlive(bool boolean) { m_alive = boolean; }
private:
	std::map<std::string, Component*> components;
	std::string m_name;
	bool m_alive;
};