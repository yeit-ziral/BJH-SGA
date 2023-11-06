#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(float radius, UINT sliceCount, UINT stackCount)
    : radius(radius), sliceCount (sliceCount), stackCount(stackCount)
{
    CreateMesh();
    CreateTangent();

    mesh = new Mesh(vertices, indices);

    material = new Material();
    material->SetShader(L"09Light");


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

void Sphere::CreateTangent()
{
    for (UINT i = 0; i < indices.size() / 3; i++)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector2 uv0 = vertices[index0].uv;
        Vector2 uv1 = vertices[index1].uv;
        Vector2 uv2 = vertices[index2].uv;

        Vector3 e01 = p1 - p0;
        Vector3 e02 = p2 - p0;

        float u1 = uv1.x - uv0.x;
        float v1 = uv1.y - uv0.y;

        float u2 = uv2.x - uv0.x;
        float v2 = uv2.y - uv0.y;

        float D = 1.0f / (u1 * v2 - v1 * u2); // Determiant (�Ǻ���) : ���⼭�� ���� ����� Ȯ����

        Vector3 tangent = D * (e01 * v2 - e02 * v1);

        vertices[index0].tangent += tangent;
        vertices[index1].tangent += tangent;
        vertices[index2].tangent += tangent;
    }

    for (VertexType& vertex : vertices)
    {
        Vector3 T = vertex.tangent;
        Vector3 N = vertex.normal;

        vertex.tangent = (T - N * Vector3::Dot(N, T)).GetNormalized();
    }
}
