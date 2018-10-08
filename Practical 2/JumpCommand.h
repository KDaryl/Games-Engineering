#pragma once
#include "Player.h"
#include "Command.h"

//Command for jumping
class JumpCommand : public Command
{
public:
	JumpCommand(Player * player) : m_player(player) {}
	void execute() { m_player->jump(); }
	void undo() { m_player->undoJump(); }
private:
	Player * m_player;
};