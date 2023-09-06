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

cbuffer LightDirection : register(b0) // pixelshader�� �����ϴ°Ŷ� World�� �ٸ�
{
    float3 lightDirection;
    float padding; // ���� �Ʒ��� �޸� �뷮�� ���� �ʾƼ� padding ����
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
    float4 pos : POSITION; // ������ǥ�� ������ float3�� �ƴ� float4�� �� ���� �ø�
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
    float4 pos : POSITION; // ������ǥ�� ������ float3�� �ƴ� float4�� �� ���� �ø�
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


SamplerState samp : register(s0); // Desc ���� ��, Sampling �� �� �������� ������ ����