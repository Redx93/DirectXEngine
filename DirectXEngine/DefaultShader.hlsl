struct VS_IN{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float3 Color : COLOR;
};

struct VS_OUT{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float3 Color : COLOR;
};
VS_OUT main(VS_IN input){
    VS_OUT output = (VS_OUT) 0;
    
    output.Pos = float4(input.Pos, 1.0f);
    output.Normal = float4(input.Normal, 1.0f);
    output.Color = input.Color;
    return output;
}
struct VS_OUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float3 Color : COLOR;
};

float4 main(VS_OUT input) : SV_Target
{

    return float4(input.Color.xyz, 0.0f);
};

