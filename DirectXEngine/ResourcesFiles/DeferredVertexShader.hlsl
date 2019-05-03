struct VS_IN
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD;
};
//-----------------------------------------------------------------------------------------
// VertexShader: VSScene
//-----------------------------------------------------------------------------------------

VS_OUT main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = float4(input.Pos, 1.0f);
	output.TextureCoord = input.TextureCoord;
	output.Normal = input.Normal;

	return output;
}