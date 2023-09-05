
#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 viewDir : VIEWDIR;
};

float4 main(VertexOutput input) : SV_TARGET
{
    float3 L = normalize(lightDirection);
    
    float diffuseIntensity = dot(input.normal, -L); //N dot L
    
    float4 albedo = diffuseMap.Sample(samp, input.uv); // 모든 반사
    
    float4 diffuse = albedo * diffuseIntensity;
    
    //SPECULAR
    float4 specular = 0;
    
    float3 reflection = normalize(reflect(L, input.normal)); // 정반사
    
    specular = dot(-reflection, input.viewDir);
    
    specular = pow(specular, 24.0f);
    
    return diffuse + specular;
}