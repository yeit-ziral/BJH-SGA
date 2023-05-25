#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	: _size(size)
{
    _type = ColliderType::RECT;
    CreateVertices();
    CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _transform->Update();
}

void RectCollider::Render()
{
    _vertexBuffer->Set(0);

    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
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

bool RectCollider::IsCollision(Vector2 pos)
{
    if (pos.x < Left() || pos.x > Right())
        return false;
    if (pos.y < Top() || pos.y > Bottom())
        return false;

    return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    Vector2 rectCenter = _transform->GetWorldPosition();
    Vector2 circleCenter = other->GetTransform()->GetWorldPosition();
    Vector2 distance = this->GetWorldSize() * 0.5f + Vector2(other->GetWorldRadius(), other->GetWorldRadius());

    Vector2 leftTop = Vector2(_vertices[0].pos.x, _vertices[0].pos.y);
    Vector2 rightTop = Vector2(_vertices[1].pos.x, _vertices[1].pos.y);
    Vector2 leftBottom = Vector2(_vertices[2].pos.x, _vertices[2].pos.y);
    Vector2 rightBottom = Vector2(_vertices[3].pos.x, _vertices[3].pos.y);

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom)
        || other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;

    if (abs(rectCenter.x - circleCenter.x) > distance.x)
        return false;
    else if (abs(rectCenter.y - circleCenter.y) > distance.y)
        return false;
    else
        return true;

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
