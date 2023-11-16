#include "Header.hlsli"

struct VertexOutput // Geometry Input
{
    float4 pos      : POSITION0;
    float2 size     : SIZE;
    matrix invView  : INVVIEW;
    matrix view     : VIEW;
    matrix proj     : PROJECTION;
};


VertexOutput main(VertexTexture input)
{
    VertexOutput output;
    
    output.pos = input.pos;
    output.size = input.uv;
    output.invView = invView;
    output.view = view;
    output.proj = proj;
    
    return output;
}