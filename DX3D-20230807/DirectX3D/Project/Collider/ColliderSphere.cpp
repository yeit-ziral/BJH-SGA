#include "Framework.h"
#include "ColliderSphere.h"

ColliderSphere::ColliderSphere(float radius, UINT stackCount, UINT sliceCount)
	: radius(radius), stackCount(stackCount), sliceCount(sliceCount)
{
    type = SPHERE;
    CreateMesh();
}

ColliderSphere::~ColliderSphere()
{
}

bool ColliderSphere::Collision(IN Ray& ray, OUT Contact* contact)
{
    Transform::UpdateWorld();

    Vector3 O = ray.origin;
    Vector3 D = ray.direction;

    Vector3 P = this->globalPosition;
    Vector3 X = O - P;

    // »ï°¢ÇÔ¼ö ÀÌ¿ëÇÑ Á¢ÃËÆÇ´Ü
    //float theta = acos(Vector3::Dot(D, X) / (D.Length() * X.Length()));

    //if (X.Length() * sin(theta) <= Radius())
    //{
    //    return true;
    //}

    // °­»ç´Ô Á¢ÃËÆÇ´Ü
    float a = Vector3::Dot(D, D);
    float b = 2 * Vector3::Dot(D, X);
    float c = Vector3::Dot(X, X) - Radius() * Radius();

    if (b * b - 4 * a * c >= 0)
    {
        if (contact != nullptr)
        {
            float t = (-b - sqrt(b * b - 4 * a * c))/ (2 * a);

            contact->distance = t;
            contact->hitPoint = O + D * t;
        }

        return true;
    }

	return false;
}

bool ColliderSphere::Collision(ColliderBox* other)
{
	return false;
}

bool ColliderSphere::Collision(ColliderSphere* other)
{
    float distance = Distance(this->globalPosition, other->globalPosition);

	return distance <= this->Radius() + other->Radius();
}

bool ColliderSphere::Collision(ColliderCapsule* other)
{
	return false;
}

void ColliderSphere::CreateMesh()
{
    for (int i = 0; i < stackCount + 1; i++)
    {
        float theta = i * XM_PI / stackCount;
        for (int j = 0; j < sliceCount + 1; j++)
        {
            float phi = j * XM_2PI / sliceCount;

            VertexType vertex;

            vertex.pos.x = radius * sin(theta) * cos(phi);
            vertex.pos.y = radius * cos(theta);
            vertex.pos.z = radius * sin(theta) * sin(phi);

            vertices.push_back(vertex);
        }
    }

    for (int j = 0; j < stackCount; j++)
    {
        for (int i = 0; i < sliceCount; i++)
        {
            indices.push_back(i + 0 + (j + 0) * (sliceCount + 1));
            indices.push_back(i + 1 + (j + 0) * (sliceCount + 1));

            indices.push_back(i + 0 + (j + 0) * (sliceCount + 1));
            indices.push_back(i + 0 + (j + 1) * (sliceCount + 1));
        }
    }

    mesh = new Mesh(vertices, indices);
}
