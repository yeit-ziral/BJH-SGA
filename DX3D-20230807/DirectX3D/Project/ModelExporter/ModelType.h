#pragma once

typedef VertexTextureNormalTangentBlend ModelVertex;

struct MeshData
{
	string name;

	UINT materialIndex;

	vector<ModelVertex> vertices;
	vector<UINT>		 indices;
};

struct NodeData
{
	int index;

	string name;

	int parent;

	XMFLOAT4X4 tranform;
};

struct BoneData
{
	int index;

	string name;

	XMFLOAT4X4 offset;
};

struct VertexWeights // 정점마다 들어가는 가중치 -> 애니메이션이 더 자연스러워 보이도록
{
	 UINT indices[4];
	float weights[4];

	void Add(const UINT& index, const float& weight)
	{
		for (UINT i = 0; i < 4; i++)
		{
			if (weights[i] == 0.0f)
			{
				indices[i] = index;
				weights[i] = weight;
				return;
			}
		}
	}

	void Normalize()
	{
		float sum = 0.0f;

		for  (UINT i = 0; i < 4;  i++)
		{
			sum += weights[i];
		}
		for (UINT i = 0; i < 4; i++)
		{
			weights[i] /= sum;
		}
	}
};