#pragma once
#include "Player.h"
#include "Command.h"

//Command for crouching
class CrouchCommand : public Command
{
public:
	CrouchCommand(Player * player) : m_player(player) {}
	void execute() { m_player->crouch(); }
	void undo() { m_player->undoCrouch(); }
private:
	Player * m_player;
};