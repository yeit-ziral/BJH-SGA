#pragma once
class Bar
{
public:
    Bar(Vector2 pos, Vector2 size);
    ~Bar();

    void Update();
    void Render(HDC hdc);

    void Move();
    void Fire();

    shared_ptr<Collider> GetCollider() { return _body; }
    shared_ptr<Bullet> GetBullet() { return _bullet; }

private:
    bool _isActive = false;

    // 컴포넌트 패턴(부품 조립 패턴) => 생산성의 증가
    shared_ptr<Collider> _body;

    shared_ptr<Bullet> _bullet;

    HBRUSH _brush;
    HPEN _pen;
};

