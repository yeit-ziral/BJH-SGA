float4 main() : SV_TARGET // -> 결과값을 OM으로 보내준다는 뜻
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f); // 1.0f -> UNORM 형식
}