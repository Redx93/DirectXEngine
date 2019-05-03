
struct VS_IN{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
    float2 TexCoordIn : TEXCOORD;
};

struct VS_OUT{
	float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 TexCoordOut : TEXCOORD;
};
//-----------------------------------------------------------------------------------------
// VertexShader: VSScene
//-----------------------------------------------------------------------------------------
VS_OUT main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;
    
    output.Pos = float4(input.Pos, 1.0f);
    output.Normal = float4(input.Normal, 1.0f);
    output.TexCoordOut = input.TexCoordIn;
	return output;
}