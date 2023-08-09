float4 main( float4 pos : POSITION ) : SV_POSITION // symentic -> 변수의 사용 용도를 적어 둔 것,  SV_POSITION (System value position)-> main의 반환값으로 리턴값이 RS(Rasterizer : 시스템)로 간다는 뜻 중간단계인 HS나 TS가 존재하면 SV_POSITION이 아닌 다른 것을 써 해당 중간단계로 보내줌
{
    float4 a = { 1, 2, 3, 4 };
	
    float4 b = a.xyzw;
    float4 b1 = a.rgba; // hlsl은 좀 더 유연하게 사용 가능 
	
	return pos;
}