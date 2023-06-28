#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	void CheckAttack();

	void Save();
	void Load();

	// esc�� ������ �� �κ��丮 Quad ������ �ϰ� Timer�� _timeScale = 0�� ����, �κ��丮 �� �� �ٽ� 1/�ֱ�� �Է�

private:
	shared_ptr<class Cup_Player> _player;

	shared_ptr<class Cup_Track> _track;
	shared_ptr<class Cup_Track> _track2;

	shared_ptr<class Cup_Monster> _monster;

	shared_ptr<Button> _button;

	shared_ptr<ActionFilterBuffer> _AFBuffer;

	shared_ptr<Effect> _effect;

	shared_ptr<Quad> _rtvQuad;
	shared_ptr<Transform> _rtvTransform;
	shared_ptr<RenderTarget> _rtv;
	shared_ptr<FilterBuffer> _filter;
};

