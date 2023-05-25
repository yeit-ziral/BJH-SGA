#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	: _size(size)
{
    _type = ColliderType::RECT;
    CreateVertices();
    Collider::CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    Collider::Update();
}

void RectCollider::Render()
{
    Collider::Render();
}

void RectCollider::CreateVertices()
{
    Vertex temp;
    Vector2 halfSize;
    halfSize.x = (_size.x) * 0.5f;
    halfSize.y = (_size.y) * 0.5f;

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 위
}

RectCollider::AABBRectInfo RectCollider::GetAABBInfo()
{
    AABBRectInfo result;
    result.left = _transform->GetWorldPosition().x - GetWorldSize().x * 0.5f;
    result.top = _transform->GetWorldPosition().y + GetWorldSize().y * 0.5f;
    result.right = _transform->GetWorldPosition().x + GetWorldSize().x * 0.5f;
    result.bottom = _transform->GetWorldPosition().y - GetWorldSize().y * 0.5f;

    return result;
}

void RectCollider::Block(shared_ptr<RectCollider> movable)
{
    if (!IsCollision(movable))
        return;

    Vector2 movableCenter = movable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();
    Vector2 dis = (this->GetWorldSize() + movable->GetWorldSize()) * 0.5f;

    Vector2 dir = movableCenter - blockCenter;

    if (dis.x - abs(dir.x) < dis.y - abs(dir.y))
    {
        float scalar = dis.x - abs(dir.x);
        if (dir.x < 0)
            scalar *= -1;
        
        movable->GetTransform()->AddVector2(Vector2(scalar, 0.0f));
    }
    else
    {
        float scalar = dis.y - abs(dir.y);
        if (dir.y < 0)
            scalar *= -1;

        movable->GetTransform()->AddVector2(Vector2(0.0f, scalar));
    }
}

bool RectCollider::IsCollision(Vector2 pos)
{
    AABBRectInfo info = GetAABBInfo();

    if (pos.x < info.left || pos.x > info.right)
        return false;
    if (pos.y < info.bottom || pos.y > info.top)
        return false;

    return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    AABBRectInfo info = GetAABBInfo();

    Vector2 leftTop = Vector2(info.left, info.top);
    Vector2 leftBottom = Vector2(info.left, info.bottom);
    Vector2 rightTop = Vector2(info.right, info.top);
    Vector2 rightBottom = Vector2(info.right, info.bottom);

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom) ||
        other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;

    if (info.right > other->GetTransform()->GetWorldPosition().x && info.left < other->GetTransform()->GetWorldPosition().x)
    {
        if (info.top - other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().y
            && info.bottom + other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().y)
            return true;
    }
    if (info.bottom < other->GetTransform()->GetWorldPosition().y && info.top > other->GetTransform()->GetWorldPosition().y)
    {
        if (info.left - other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().x
            && info.right + other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().x)
            return true;
    }
    return false;

    // 많은 정점을 다 확인해야되서 좋지 않음
    /*auto it = find_if(other->GetVertices().begin(), other->GetVertices().end(), [this](const Vertex& ver)
    {
        float a = ver.pos.x;
        float b = ver.pos.y;

        return (a > Left() && a < Right()) && (b < Top() && b > Bottom());
    });

    if (it != other->GetVertices().end())
        return true;
    else
        return false;*/
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    Vector2 center1 = _transform->GetWorldPosition();
    Vector2 center2 = other->GetTransform()->GetWorldPosition();
    Vector2 distance = (this->GetWorldSize() + other->GetWorldSize()) * 0.5f;

    if (abs(center1.x - center2.x) > distance.x)
        return false;
    else if (abs(center1.y - center2.y) > distance.y)
        return false;
    else
        return true;
}
