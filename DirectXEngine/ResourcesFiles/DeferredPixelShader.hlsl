Texture2D objectTexture : register(t0);
SamplerState textureSampler;

struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
	float3 worldPos : WORLDPOS;
	float3 camPos : CAMPOS;
};

struct DeferredPixelOut
{
	float4 textBuffer		: SV_Target0;
	float4 normalBuffer		: SV_Target1;
	float4 positionBuffer	: SV_Target2;
};

DeferredPixelOut main(GSOutput input)
{
	DeferredPixelOut DefPOut;
	DefPOut.textBuffer = objectTexture.Sample(textureSampler, input.tex);
	DefPOut.normalBuffer = float4(input.normal, 1.0f);
	DefPOut.positionBuffer = float4(input.worldPos, 1.0f);

	return DefPOut;
}