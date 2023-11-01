cbuffer World : register(b0)
{
    matrix world;
};

cbuffer View : register(b1)
{
    matrix view;
    matrix invView;
};

cbuffer Proj : register(b2)
{
    matrix proj;
};

cbuffer LightDirection : register(b0) // pixelshader에 적용하는거라서 World에 할당된 b0와 다름
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
    float4 mEmissive;
    
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    int hasAlphaMap;
    
    float shininess;
    // 받아오는곳은 패딩 필요 없음
};

struct Frame
{
    int clip;
    uint curFrame;
    float time;
    float speed;
};

struct Motion
{
    float takeTime;
    float tweenTime;
    float runningTime;
    float padding2;
    
    Frame cur, next;
};

cbuffer FrameBuffer : register(b3)
{
    Motion motion;
}

Texture2DArray transformMap : register(t0);

//struct VertexInput
//{
//    float4 pos : POSITION; // 동차좌표계 쓰려고 float3가 아닌 float4로 한 차수 올림
//    float4 color : COLOR;
//};

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

struct VertexTextureNormalTangent
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VertexTextureNormalTangentAlpha
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 alpha : ALPHA;
};

struct VertexTextureNormalTangentBlend
{
    float4 pos      : POSITION;
    float2 uv       : UV;
    float3 normal   : NORMAL;
    float3 tangent  : TANGENT;
    float4 indices  : BLENDINDICES; // 정점에 영향 받을 bone의 index들
    float4 weight   : BLENDWEIGHTS; // 영향 받을 정도
};

Texture2D  diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);


SamplerState samp : register(s0); // Desc 같은 것, Sampling 할 때 세부적인 사항을 설명