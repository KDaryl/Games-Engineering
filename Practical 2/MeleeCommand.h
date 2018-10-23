#pragma once
#include "Player.h"
#include "Command.h"

//Command for melee
class MeleeCommand : public Command
{
public:
	MeleeCommand(Player * player) : m_player(player) {}
	void execute() { m_player->getAnimation().melee(); }
	void undo() { m_player->getAnimation().idle(); }
private:
	Player * m_player;
};