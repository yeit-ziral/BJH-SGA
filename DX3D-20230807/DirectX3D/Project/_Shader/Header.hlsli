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

#define MAX_INSTANCE 128

cbuffer FrameInstancingBuffer : register(b4) // 
{
    Motion motions[MAX_INSTANCE];
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

struct VertexInstancing
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : BLENDINDICES; // 정점에 영향 받을 bone의 index들
    float4 weight : BLENDWEIGHTS; // 영향 받을 정도
    
    matrix transform : INSTANCE_TRANSFORM;
    uint index       : INSTANCE_INDEX;
};

Texture2D  diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);


SamplerState samp : register(s0); // Desc 같은 것, Sampling 할 때 세부적인 사항을 설명

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
    
    
    [unroll] // shader에만 쓰이는 명령어, 반복문에 쓰는 명령어, 반복문을 펼쳐서 쓴것처럼 바꿔줌-> 속도가 빨라지지만 메모리를 더 많이 차지함(지역변수를 다 반복한 만큼 생성해서 쓰기 때문)
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
    
    
    [unroll] // shader에만 쓰이는 명령어, 반복문에 쓰는 명령어, 반복문을 펼쳐서 쓴것처럼 바꿔줌-> 속도가 빨라지지만 메모리를 더 많이 차지함(지역변수를 다 반복한 만큼 생성해서 쓰기 때문)
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