cbuffer World : register(b0)
{
    matrix world;

};

cbuffer View : register(b1)
{
    matrix view;
    matrix inverseView;
};

cbuffer Proj : register(b2)
{
    matrix projection;
};

cbuffer LightDirection : register(b3)
{
    float3 lightDirection;
};

struct VertexInput
{
    float4 pos : POSITION; // 동차좌표계 쓰려고 float3가 아닌 float4로 한 차수 올림
    float4 color : COLOR;
};

struct VertexColor
{
    float4 pos : POSITIONT;
    float4 color : COLOR;
};

struct VertexTexture
{
    float4 pos : POSITION;
    float2 uv : UV;
};


struct VertexTextureNormal
{
    float4 pos : POSITION; // 동차좌표계 쓰려고 float3가 아닌 float4로 한 차수 올림
    float2 uv : UV;
    float3 normal : NORMAL;
};

struct VertexColorNormal
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};

Texture2D diffuseMap : register(t0);
SamplerState samp : register(s0); // Desc 같은 것, Sampling 할 때 세부적인 사항을 설명