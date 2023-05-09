struct VertexInput
{
	float4 pos : POSITION; /*½Ã¸àÆ½ ³×ÀÓ*/
	float4 color :COLOR;
};

struct PixelInput
{
	float4 pos : SV_POSITION; // Symentic Name... SV->SystemValue
	float4 color : COLOR;
};


PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.pos = input.pos;
	output.color = input.color;

	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return input.color;
}