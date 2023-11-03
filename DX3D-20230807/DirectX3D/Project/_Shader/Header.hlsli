cbuffer World : register(b0)
{
    matrix world;
    int hasAnimation;
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

cbuffer LightDirection : register(b0) // pixelshader�� �����ϴ°Ŷ� World�� �Ҵ�� b0�� �ٸ�
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
    float4 mEmissive;
    
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    int hasAlphaMap;
    
    float shininess;
    // �޾ƿ��°��� �е� �ʿ� ����
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

#define MAX_INSTANCE 128

cbuffer FrameInstancingBuffer : register(b4) // 
{
    Motion motions[MAX_INSTANCE];
}

Texture2DArray transformMap : register(t0);

//struct VertexInput
//{
//    float4 pos : POSITION; // ������ǥ�� ������ float3�� �ƴ� float4�� �� ���� �ø�
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
    float4 indices  : BLENDINDICES; // ������ ���� ���� bone�� index��
    float4 weight   : BLENDWEIGHTS; // ���� ���� ����
};

struct VertexInstancing
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : BLENDINDICES; // ������ ���� ���� bone�� index��
    float4 weight : BLENDWEIGHTS; // ���� ���� ����
    
    matrix transform : INSTANCE_TRANSFORM;
    uint index       : INSTANCE_INDEX;
};

Texture2D  diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);


SamplerState samp : register(s0); // Desc ���� ��, Sampling �� �� �������� ������ ����

///Light

struct Light
{
    float4 color;
    
    float3 directon;
    int    type;
    
    float3 posiiton;
    float  range;
    
    float inner;
    float outer;
    float length;
    int   active;
};

struct LightData
{
    float3 normal;
    float4 difuseColor;
    float4 emissive;
    float4 specularIntecsity;
    
    float shininess;
    
    float3 viewPos;
    float3 worldPos;
};

struct LightPixelInput
{
    float4 pos       : SV_POSITION;
    float2 uv        : UV;
    float3 normal    : NORMAL;
    float3 tangent   : TANGENT;
    float3 binormal  : BINORMAL;
    float3 viewPos   : POSITION0;
    float3 worldPos  : POSITION1;
};



matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix curAnim, nextAnim;
    matrix cur, next;
    
    float4 c0, c1, c2, c3;
    
    float4 n0, n1, n2, n3;
    
    int clipIndex[2];
    int curFrame[2];
    float time[2];
    
    clipIndex[0] = motion.cur.clip;
    curFrame[0] = motion.cur.curFrame;
    time[0] = motion.cur.time;
        
    clipIndex[1] = motion.next.clip;
    curFrame[1] = motion.next.curFrame;
    time[1] = motion.next.time;
    
    
    [unroll] // shader���� ���̴� ��ɾ�, �ݺ����� ���� ��ɾ�, �ݺ����� ���ļ� ����ó�� �ٲ���-> �ӵ��� ���������� �޸𸮸� �� ���� ������(���������� �� �ݺ��� ��ŭ �����ؼ� ���� ����)
    for (int i = 0; i < 4; i++)
    {
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[0], clipIndex[0], 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[0], clipIndex[0], 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[0], clipIndex[0], 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[0], clipIndex[0], 0));
                                                                    
        cur = matrix(c0, c1, c2, c3);
        
        n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[0] + 1, clipIndex[0], 0));
        n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[0] + 1, clipIndex[0], 0));
        n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[0] + 1, clipIndex[0], 0));
        n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[0] + 1, clipIndex[0], 0));
                                                                    
        next = matrix(n0, n1, n2, n3);
        
        
        curAnim = lerp(cur, next, time[0]);
        
        
        [flatten]
        if (clipIndex[1] > -1)
        {
            c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[1], clipIndex[1], 0));
            c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[1], clipIndex[1], 0));
            c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[1], clipIndex[1], 0));
            c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[1], clipIndex[1], 0));
                                                                    
            cur = matrix(c0, c1, c2, c3);
        
            n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[1] + 1, clipIndex[1], 0));
            n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[1] + 1, clipIndex[1], 0));
            n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[1] + 1, clipIndex[1], 0));
            n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[1] + 1, clipIndex[1], 0));
                                                                    
            next = matrix(n0, n1, n2, n3);
        
        
            nextAnim = lerp(cur, next, time[1]);
            
            curAnim = lerp(curAnim, nextAnim, motion.tweenTime);
        }
        
        transform += mul(weights[i], curAnim);
    }
    
    return transform;
}

matrix SkinWorld(uint instancedIndex, float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix curAnim, nextAnim;
    matrix cur, next;
    
    float4 c0, c1, c2, c3;
    
    float4 n0, n1, n2, n3;
    
    int clipIndex[2];
    int curFrame[2];
    float time[2];
    
    clipIndex[0] = motions[instancedIndex].cur.clip;
    curFrame[0] = motions[instancedIndex].cur.curFrame;
    time[0] = motions[instancedIndex].cur.time;
        
    clipIndex[1] = motions[instancedIndex].next.clip;
    curFrame[1] = motions[instancedIndex].next.curFrame;
    time[1] = motions[instancedIndex].next.time;
    
    
    [unroll] // shader���� ���̴� ��ɾ�, �ݺ����� ���� ��ɾ�, �ݺ����� ���ļ� ����ó�� �ٲ���-> �ӵ��� ���������� �޸𸮸� �� ���� ������(���������� �� �ݺ��� ��ŭ �����ؼ� ���� ����)
    for (int i = 0; i < 4; i++)
    {
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[0], clipIndex[0], 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[0], clipIndex[0], 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[0], clipIndex[0], 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[0], clipIndex[0], 0));
                                                                    
        cur = matrix(c0, c1, c2, c3);
        
        n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[0] + 1, clipIndex[0], 0));
        n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[0] + 1, clipIndex[0], 0));
        n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[0] + 1, clipIndex[0], 0));
        n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[0] + 1, clipIndex[0], 0));
                                                                    
        next = matrix(n0, n1, n2, n3);
        
        
        curAnim = lerp(cur, next, time[0]);
        
        
        [flatten]
        if (clipIndex[1] > -1)
        {
            c0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[1], clipIndex[1], 0));
            c1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[1], clipIndex[1], 0));
            c2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[1], clipIndex[1], 0));
            c3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[1], clipIndex[1], 0));
                                                                    
            cur = matrix(c0, c1, c2, c3);
        
            n0 = transformMap.Load(int4(indices[i] * 4 + 0, curFrame[1] + 1, clipIndex[1], 0));
            n1 = transformMap.Load(int4(indices[i] * 4 + 1, curFrame[1] + 1, clipIndex[1], 0));
            n2 = transformMap.Load(int4(indices[i] * 4 + 2, curFrame[1] + 1, clipIndex[1], 0));
            n3 = transformMap.Load(int4(indices[i] * 4 + 3, curFrame[1] + 1, clipIndex[1], 0));
                                                                    
            next = matrix(n0, n1, n2, n3);
        
        
            nextAnim = lerp(cur, next, time[1]);
            
            curAnim = lerp(curAnim, nextAnim, motions[instancedIndex].tweenTime);
        }
        
        transform += mul(weights[i], curAnim);
    }
    
    return transform;
}