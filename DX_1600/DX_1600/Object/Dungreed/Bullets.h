#pragma once
class Bullets
{
public:
    Bullets(Vector2 pos);
    ~Bullets();

    void Update();
    void Render();

    void Shoot(const Vector2& dir, Vector2 startPos);

    bool IsActive() { return _isActive; }

private:
    bool _isActive = false;

    float _speed = 0.2f;
    Vector2 _dir = Vector2();

    shared_ptr<Quad> _bullet;
};

