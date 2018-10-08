#pragma once
#include "Player.h"
#include "Command.h"

//Command for using shield
class ShieldCommand : public Command
{
public:
	ShieldCommand(Player * player) : m_player(player) {}
	void execute() { m_player->shield(); }
	void undo() { m_player->undoShield(); }
private:
	Player * m_player;
};