#pragma once
#include "Player.h"
#include "Command.h"

//Command for firing
class FireCommand : public Command
{
public:
	FireCommand(Player * player) : m_player(player) {}
	void execute() { m_player->getAnimation().fire(); }
	void undo() { m_player->getAnimation().idle(); }
private:
	Player * m_player;
};