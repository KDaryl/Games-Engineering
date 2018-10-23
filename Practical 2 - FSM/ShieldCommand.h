#pragma once
#include "Player.h"
#include "Command.h"

//Command for using shield
class ShieldCommand : public Command
{
public:
	ShieldCommand(Player * player) : m_player(player) {}
	void execute() { m_player->getAnimation().shield(); }
	void undo() { m_player->getAnimation().idle(); }
private:
	Player * m_player;
};