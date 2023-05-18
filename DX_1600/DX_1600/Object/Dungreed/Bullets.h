#pragma once
class Bullets
{
    Bullets(wstring file, Vector2 scale);
    ~Bullets();

    void Update();
    void Render();

    void SetPosition(Vector2 pos) { _bullet->GetTransform()->SetPosition(pos); }
    void SetParent(shared_ptr<Transform> parent) { _bullet->GetTransform()->SetParent(parent); _revolution->SetParent(parent); }

    void Shoot(const Vector2& dir, float speed);

    bool IsActive() { return _isActive; }
    void SetActive(bool value) { _isActive = value; }

private:
    bool _isActive = false;
    float _speed = 30.0f;
    Vector2 _direction = Vector2(0.0f, 0.0f);

    shared_ptr<Quad> _bullet;
    shared_ptr<Transform> _revolution;
};

