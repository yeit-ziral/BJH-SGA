#pragma once
class Button
{
public:
	Button(wstring path, Vector2 size);
	~Button();

	void Updata();
	void PostRender(); // 항상 맨 뒤에 와야되기 때문에 PostRender에 만듬

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	void SetEvent(CallBack callBack) { _event = callBack; }

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<ButtonBuffer> _buttonBuffer;

	CallBack _event;
};

