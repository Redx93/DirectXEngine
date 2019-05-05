struct GS_IN
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 tex : TEXCOORD;
};

struct GSOutput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
    float3 worldPos : WORLDPOS;
    float3 camPos : CAMPOS;
};

cbuffer CB_PER_FRAME : register(b0){
    float4x4 view; //16
    float4x4 projection; 
    float3 camPos; //12
    float padding;//4 nu 16
}
cbuffer FRAME : register(b1){ 
    float4x4 world; //16byte
}


[maxvertexcount(3)]
void main(triangle GS_IN input[3], inout TriangleStream<GSOutput> OutputStream)
{
    GSOutput output;

    float3 v = input[1].Pos - input[0].Pos;
    float3 u = input[2].Pos - input[0].Pos;
    float3 normal = normalize(cross(v, u));
    matrix mvp = mul(projection, mul(view, world));

	float3 worldPos = (mul(((float3x3) view), input[0].Pos.xyz));
	float3 worldnormal = (mul((float3x3) view, normal));



    //(v0 - p) * N >  = > 0
    // p  = viewPoint;
    float3 dir =  camPos- worldPos;
    if (dot(input[0].Pos,normal) >= 0.0f)
    {
        for (uint i = 0; i < 3; i++)
        {
            output.pos = mul(mvp, input[i].Pos);
            output.normal = normalize(mul((float3x3) world, input[i].Normal));
            output.tex = input[i].tex;
            output.worldPos = mul((float3x3) world, input[i].Pos.xyz);
            output.camPos = camPos;
            OutputStream.Append(output);
         
        }
     
    }
    OutputStream.RestartStrip();
}