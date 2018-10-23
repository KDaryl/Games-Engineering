#pragma once
#include "Player.h"
#include "Command.h"

//Command for firing
class FireCommand : public Command
{
public:
	FireCommand(Player * player) : m_player(player) {}
	void execute() { m_player->fire(); }
	void undo() { m_player->undoFire(); }
private:
	Player * m_player;
};