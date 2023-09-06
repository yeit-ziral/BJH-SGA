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

cbuffer LightDirection : register(b0) // pixelshader에 적용하는거라서 World와 다름
{
    float3 lightDirection;
    float padding; // 위와 아래의 메모리 용량이 맞지 않아서 padding 넣음
    float4 ambientLight;
};

cbuffer MaterialBuffer : register(b1)
{
    float4 mDiffuse;
    float4 mSpecular;
    float4 mAmbient;
    
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    
    float shininess;
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

Texture2D  diffuseMap : register(t0);
Texture2D specularMap : register(t1);


SamplerState samp : register(s0); // Desc 같은 것, Sampling 할 때 세부적인 사항을 설명