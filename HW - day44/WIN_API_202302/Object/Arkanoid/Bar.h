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

    // ������Ʈ ����(��ǰ ���� ����) => ���꼺�� ����
    shared_ptr<Collider> _body;

    shared_ptr<Bullet> _bullet;

    HBRUSH _brush;
    HPEN _pen;
};

