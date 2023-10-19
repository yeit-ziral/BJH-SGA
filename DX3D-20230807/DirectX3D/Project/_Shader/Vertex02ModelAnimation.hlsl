#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT; // uv�� x��
    float3 binormal : BINORMAL; // uv�� y��
    float3 viewDir : VIEWDIR;
};

matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix curAnim, nextAnim;
    matrix cur, next;
    
    float4 c0, c1, c2, c3;
    
    float4 n0, n1, n2, n3;
    
    int     clipIndex[2];
    int     curFrame[2];
    float   time[2];
    
    clipIndex[0] = motion.cur.clip;
    curFrame[0]  = motion.cur.curFrame;
    time[0]      = motion.cur.time;
        
    clipIndex[1] = motion.next.clip;
    curFrame[1]  = motion.next.curFrame;
    time[1]      = motion.next.time;
    
    
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

VertexOutput
    main(VertexTextureNormalTangentBlend input)
{
    VertexOutput output;
    
    /////////////////////////
    
    matrix transform = mul(SkinWorld(input.indices, input.weight), world);
    
    output.pos = mul(input.pos, transform);
    ////////////////////////
    
    //output.pos = mul(output.pos, world);
    
    float3 cameraPos = invView._41_42_43;
    
    output.viewDir = normalize(output.pos.xyz - cameraPos);
    
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.uv = input.uv;
    
    output.normal = normalize(mul(input.normal, (float3x3) world));

    output.tangent = normalize(mul(input.tangent, (float3x3) world));
    
    output.binormal = cross(output.normal, output.tangent);
    
    return output;
}