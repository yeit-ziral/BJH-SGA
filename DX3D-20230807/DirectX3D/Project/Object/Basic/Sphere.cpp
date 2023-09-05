#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(float radius, UINT sliceCount, UINT stackCount)
    : radius(radius), sliceCount (sliceCount), stackCount(stackCount)
{
    CreateMesh();

    mesh = new Mesh(vertices, indices);

    material = new Material();
    material->SetShader(L"Specular");
    material->SetDiffuseMap(L"Landscape/Bricks.png");

    worldBuffer = new MatrixBuffer();
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
    worldBuffer->SetData(world);
    worldBuffer->SetVSBuffer(0);

    material->SetMaterial();
        mesh->SetMesh();

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Sphere::CreateMesh()
{
    for (int i = 0; i < stackCount + 1; i++)
    {
        float theta = i * XM_PI / stackCount;
        for (int j = 0; j < sliceCount + 1; j++)
        {
            VertexType vertex;
            float phi = j * XM_2PI / sliceCount;

            vertex.pos.x = radius * sin(theta) * cos(phi);
            vertex.pos.y = radius * cos(theta);
            vertex.pos.z = radius * sin(theta) * sin(phi);

            vertex.normal = vertex.pos / radius;

            vertex.uv.x = j / (float)sliceCount;
            vertex.uv.y = i / (float)stackCount;

            vertices.push_back(vertex);
        }
    }

    for (int j = 0; j < stackCount; j++)
    {
        for (int i = 0; i < sliceCount; i++)
        {
            indices.push_back(i + 0 + (j + 0) * (sliceCount + 1));
            indices.push_back(i + 1 + (j + 0) * (sliceCount + 1));
            indices.push_back(i + 0 + (j + 1) * (sliceCount + 1));

            indices.push_back(i + 0 + (j + 1) * (sliceCount + 1));
            indices.push_back(i + 1 + (j + 0) * (sliceCount + 1));
            indices.push_back(i + 1 + (j + 1) * (sliceCount + 1));
        }
    }
}
