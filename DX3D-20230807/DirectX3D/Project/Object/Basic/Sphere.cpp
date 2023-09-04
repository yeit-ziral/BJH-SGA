#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(Vector4 color, float radius)
    : radius(radius)
{
    material = new Material(L"Diffuse");
    //material = new Material(L"DiffuseColor");

    worldBuffer = new MatrixBuffer();

    CreateMesh(color);
    CreateNormal();

    mesh = new Mesh(vertices, indices);
}

Sphere::~Sphere()
{
    delete mesh;
    delete material;
    delete worldBuffer;
}

void Sphere::Update()
{
    Transform::Update();

    worldBuffer->SetData(world);
}

void Sphere::Render()
{
    material->SetMaterial();
    mesh->SetMesh();

    worldBuffer->SetVSBuffer(0);

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Sphere::CreateMesh(Vector4 color)
{
    for (int i = 0; i <= latitudes; i++)
    {
        float theta = i * XM_PI / latitudes;
        for (int j = 0; j < longitudes; j++)
        {
            VertexColorNormal vertex;
            float phi = j * 2 * XM_PI / longitudes;

            vertex.pos.x = radius * sin(theta) * cos(phi);
            vertex.pos.y = radius * cos(theta);
            vertex.pos.z = radius * sin(theta) * sin(phi);

            vertex.normal.x = sin(theta) * cos(phi);
            vertex.normal.y = cos(theta);
            vertex.normal.z = sin(theta) * sin(phi);
        }
    }

    for (int i = 0; i < latitudes; i++)
    {
        for (int j = 0; j < longitudes; j++)
        {
            UINT LB = j + 0 + (i + 0) * (longitudes + 1);
            UINT RB = j + 1 + (i + 0) * (longitudes + 1);
            UINT LT = j + 0 + (i + 1) * (longitudes + 1);
            UINT RT = j + 1 + (i + 1) * (longitudes + 1);

            indices.push_back(LT);
            indices.push_back(RT);
            indices.push_back(LB);

            indices.push_back(LB);
            indices.push_back(RT);
            indices.push_back(RB);
        }
    }
}

void Sphere::CreateNormal()
{
    for (UINT i = 0; indices.size() / 3; i++)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector3 v01 = p1 - p0;
        Vector3 v02 = p2 - p0;

        Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

        vertices[index0].normal += normal;
        vertices[index1].normal += normal;
        vertices[index2].normal += normal;
    }
}
