Texture2D	textureTexture: register(t0);
Texture2D	textureNormal: register(t1);
Texture2D	texturePos: register(t2);

SamplerState textureSampler;

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD;
	float4 worldPos : WORLDPOS;
};

struct PixelOut
{
	float4 colour : SV_Target;
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
cbuffer DISPLAY : register(b1)
{
	float display;
	float3 padding;
}

float SpotLight(float3 pos, float3 worldPos)
{
	float intensity = 0;
	float3 dir = normalize(pos);
	float3 vectorToLight = normalize(worldPos - pos);
	float value = dot(dir, vectorToLight);

	//the vertex lies beyond the outer
	if (value <= 0.5)
	{ //no light
		intensity = 0;
	}
	else
	{
		if (value <= 0.2)
		{
			float lf = (cos(value) - cos(0.5 / 2)) /
				(cos(0.25 / 2) - cos(0.5 / 2));
			float falloff = 0.6;
			intensity = lf * falloff;


		}
		else
			intensity = 1;
	}

	return intensity;

}

PixelOut main(VS_OUT input)
{
	PixelOut psOut;
	float3 normal = textureNormal.Sample(textureSampler, input.TextureCoord).rgb;
	float3 diffuse = textureTexture.Sample(textureSampler, input.TextureCoord).rgb;
	psOut.colour = (float4)(diffuse, 1.0f);
	float4 totalLights;

	for (int i = 0; i < 2; i++)
	{
		float3 ambientLight = light[i].AmbientColor * light[i].AmbientLight;
		float3 appliedLight = ambientLight;
		float intensity = SpotLight(light[i].position, input.worldPos);
		float3 diffuseLight = intensity * light[i].Strength*  light[i].LightColor;
		appliedLight += diffuseLight;
		totalLights += float4(saturate(appliedLight), 1.0);
	}
	//psOut.colour = float4(diffuse, 1.0f);
	//psOut.colour = float4(normal, 1.0f);
	switch (display)
	{
	case 0: //All buffers
		psOut.colour = float4(diffuse, 1.0f) + totalLights;
		break;
	case 1: //Normal buffer only
		psOut.colour = float4(normal, 1.0f);
		break;
	case 2: //Pos buffer only
		float depth = texturePos.Sample(textureSampler, input.TextureCoord).b;
		psOut.colour = float4(depth, depth, depth, 1.0f);
		break;
	case 3: //Texture buffer only
		psOut.colour = float4(diffuse, 1.0f);
		break;
	case 4: //Unused. (Could use for normal mapping)
		psOut.colour = float4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}


	return psOut;
};
