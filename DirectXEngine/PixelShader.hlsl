#include "Lights.hlsl"

Texture2D txDiffuse : register(t0);
SamplerState sampAni;

struct VS_OUT
{
	float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 TexCoordIn : TEXCOORD;
    float3 worldPos : WORLDPOS;
    float3 camPos : CAMPOS;
};
struct LightPixelShader
{
    float lightType;
    float3 AmbientColor;
    float AmbientLight;
    float3 LightColor;
    float Strength;
    float3 position;
};

cbuffer LIGHT : register(b0)
{
    LightPixelShader light[2];
};


float4 main(VS_OUT input) : SV_Target
{
    
    //float3 s = txDiffuse.Sample(sampAni, input.TexCoordIn).xyz;
    //float4 finalColor = float4(0.2, 0.2, 0.2, 1.0f) * float4(s, 1.0f);
    //float4 finalColor1 = float4(0.2, 0.2, 0.2, 1.0f);
    //float3 lightPosition = float3(0.0f, 0.0f, -2.0f);
    //float3 lightDirection = (lightPosition - input.worldPos.xyz);
    //float diffuse = (dot(normalize(lightDirection), (input.Normal)));
    //diffuse = max(0.0f, diffuse);
    //float3 Color = s * diffuse  * (1.0 / (length(lightDirection)));
    //finalColor += float4(Color.xyz, 0.0f); // finalColor;
    //finalColor = min(finalColor, float4(1.0f, 1.0f, 1.0f, 1.0f)); 
    //return float4(s, 1.0f);
    float4 finalColor = float4(0.2, 0.2, 0.2, 1.0);
    float3 sampleColor = txDiffuse.Sample(sampAni, input.TexCoordIn).xyz;
    for (int i = 0; i < 2; i++)
    {
        float3 ambientLight = light[i].AmbientColor * light[i].AmbientLight;
        float3 appliedLight = ambientLight;
      //  float intensity = CalculateLight(light[i].lightType, light[i].position, input.worldPos, input.Normal);
       float intensity = SpotLight(light[i].position, input.worldPos);
      //  float intensity = PointLight(input.Normal, light[i].position, input.worldPos);
        float3 diffuseLight = intensity * light[i].Strength*  light[i].LightColor;
            appliedLight += diffuseLight;
        finalColor += /* float4(appliedLight, 1.0f)*/float4(saturate(appliedLight), 1.0);
    }
    return finalColor + float4(sampleColor.xyz, 0.0f);
    //return float4(ambientLight.xyz, 0.0f);
};





//float3 sampleColor = txDiffuse.Sample(sampAni, input.TexCoordIn).xyz;
//float3 ambientLight = AmbientColor * AmbientLight;
//float3 appliedLight = ambientLight;

//float intensity = CalculateLight(lightType, position, input.worldPos, input.Normal);

//   // float3 vectorToLight = normalize(position - input.worldPos);
//   // float intensity = PointLight(input.Normal, position, input.worldPos);
//   // float intensity = SpotLight(position, input.worldPos);
//    //float3 diffuse = dot(intensity, input.Normal);
//    //       diffuse = max(0.0f, diffuse);
//float3 diffuseLight = intensity * 0.5 * LightColor;
//            appliedLight +=
//diffuseLight;
//float3 finalColor = sampleColor * appliedLight /*saturate(appliedLight);
//    return float4(finalColor, 1.0f);
