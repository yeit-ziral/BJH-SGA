#pragma once
class Cup_Track
{
public:
	Cup_Track();
	~Cup_Track();

	void Update();
	void Render();

	shared_ptr<Collider> GetColider() { return _col; }

	Vector2 GetTrackSize() { return trackSize; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private:
	shared_ptr<Collider> _col;
	shared_ptr<Quad> _track;
	shared_ptr<Transform> _transform;

	Vector2 trackSize;
};

