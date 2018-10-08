#pragma once
#include "Player.h"
#include "Command.h"

//Command for melee
class MeleeCommand : public Command
{
public:
	MeleeCommand(Player * player) : m_player(player) {}
	void execute() { m_player->melee(); }
	void undo() { m_player->undoMelee(); }
private:
	Player * m_player;
};