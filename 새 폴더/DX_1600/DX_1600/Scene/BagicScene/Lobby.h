#pragma once
class Lobby : public Scene
{
public:
	Lobby();
	virtual ~Lobby();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Render() override;

	void Save();
	void Load();

private:
	shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;

	shared_ptr<class Potal> _potal;
};