#pragma once
class Bullets
{
public:
    Bullets();
    ~Bullets();

    void Update();
    void Render();

    void SetPos(const Vector2& pos) { _bullet->GetTransform()->SetPosition(pos); }

    void Shoot(const Vector2& dir, Vector2 startPos);

    bool IsActive() { return _isActive; }

    void SetActive(bool value) { _isActive = value; }

private:
    bool _isActive = false;

    float _speed = 100.0f;
    Vector2 _dir = Vector2();

    shared_ptr<Quad> _bullet;
};

