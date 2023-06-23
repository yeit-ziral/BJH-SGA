#pragma once
class Button
{
public:
	Button(wstring path, Vector2 size);
	~Button();

	void Updata();
	void PostRender(); // �׻� �� �ڿ� �;ߵǱ� ������ PostRender�� ����

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	void SetEvent(CallBack callBack) { _event = callBack; }

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<ButtonBuffer> _buttonBuffer;

	CallBack _event;
};

