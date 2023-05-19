#pragma once
class Bullets
{
public:
    Bullets(wstring file, Vector2 scale);
    ~Bullets();

    void Update();
    void Render();

    void SetPosition(Vector2 pos) { _bullet->GetTransform()->SetPosition(pos); }
    void SetParent(shared_ptr<Transform> parent) { _bullet->GetTransform()->SetParent(parent); _revolution->SetParent(parent); }

    void Shoot(const Vector2& dir, Vector2 startPos);

    bool IsActive() { return _isActive; }
    void SetActive(bool value) { _isActive = value; }

private:
    bool _isActive = false;
    float _speed = 0.2f;
    Vector2 _direction = Vector2();

    shared_ptr<Quad> _bullet;
    shared_ptr<Transform> _revolution;
};

