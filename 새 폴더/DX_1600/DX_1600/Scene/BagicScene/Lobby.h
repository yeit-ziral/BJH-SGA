#pragma once
class Lobby
{
public:
	Lobby();
	~Lobby();

	void Update();
	void Render();


private:
	shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;
};