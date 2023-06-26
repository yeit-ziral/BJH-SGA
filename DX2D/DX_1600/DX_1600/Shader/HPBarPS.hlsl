Texture2D map: register(t0);
SamplerState samp : register(s0);

cbuffer HPBarBuffer : register(b0)
{
	int maxHP;
	int curHP;
	int padding[2];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = map.Sample(samp, input.uv);
	float ratio = (float)curHP / (float)maxHP;
	if (ratio > 1)
		ratio = 1;
	if (input.uv.x > ratio)
		return float4 (0, 0, 0, 0);

	return color;
}