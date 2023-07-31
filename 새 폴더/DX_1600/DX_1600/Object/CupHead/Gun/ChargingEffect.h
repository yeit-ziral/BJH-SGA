#pragma once
class ChargingEffect
{
public:
	ChargingEffect();
	~ChargingEffect();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop);

	void SetParent(shared_ptr<Transform> a) { _transform->SetParent(a); }

	void SetPosition(Vector2 v) { _transform->SetPosition(v); }

	void Play() { _isActive = true;  _action->Play(); }

	bool _isActive = false;

	void SetLeft();
	void SetRight();

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<Action> _action;

	shared_ptr<Sprite> _sprite;

	float _timer = 0.0f;
	const float _inactiveTime = 3.0f;
};

