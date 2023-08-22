#pragma once
class Lobby
{
public:
	Lobby();
	~Lobby();

private:
	shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;
};