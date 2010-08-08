//---- VERTEX PROGRAM DECLARATIONS

struct VS_OUTPUT 
{
    float4 oPosition : POSITION;
	float2 oUv : TEXCOORD0;
	float4 oLightPosition : TEXCOORD1;
	float3 oEyePosition : TEXCOORD2;
	float4 oPositionIn : TEXCOORD3;
	float4 oNormalIn : TEXCOORD4;
	float2 oUv1 : TEXCOORD5; 
};

//---- VERTEX PROGRAM

float4 lightPosition;
float3 eyePosition;
float4x4 worldViewProj;

VS_OUTPUT rim_normalsVS
(
	in float4 position : POSITION,
	in float3 normal : NORMAL,
	in float2 uv : TEXCOORD0, 
	in float3 tangent : TEXCOORD1
)
{
	VS_OUTPUT Output;
	Output.oPosition = mul( worldViewProj , position );
	Output.oUv = uv;
	Output.oUv1 = uv;
	Output.oLightPosition = lightPosition;
	Output.oEyePosition = eyePosition;
	Output.oPositionIn = position;
	Output.oNormalIn = float4( normal, 1 );
    return( Output );
}

//---- FRAGMENT PROGRAM DECLARATIONS

sampler textureDiffuse : register(s0);
sampler textureNormal : register(s1);
sampler textureModulate : register(s2);

struct PS_INPUT 
{
       float2 uv : TEXCOORD0;
       float4 lightPosition : TEXCOORD1;
       float3 eyePosition : TEXCOORD2;
       float4 positionIn : TEXCOORD3;
       float4 normalIn : TEXCOORD4;
       float2 uv1 : TEXCOORD5;
       float4 color : COLOR;
};

float4 lightDiffuse;
float4 lightSpecular;
float4 ambient;
float4 rimStrength;
float modulate_factor;
float alpha_modulate;

float4 rim_normalsPS(PS_INPUT Input) : COLOR0
{
    float4 oColor;
	float3 eyeDirection = normalize( Input.eyePosition - Input.positionIn.xyz );
	float3 lightDirection = normalize( Input.lightPosition.xyz - ( Input.positionIn * Input.lightPosition.w ).xyz );
	float3 halfAngle = normalize( lightDirection + eyeDirection );
	
	float4 normal = normalize( Input.normalIn * tex2D( textureNormal, Input.uv ) );
	
	float NdotL = dot( lightDirection, normal );
	float NdotH = dot( halfAngle, normal );
	float4 Lit = lit( NdotL, NdotH, 0 );
	
	float4 dff = tex2D( textureDiffuse, Input.uv1 );
	
	float rimLightValue =  saturate( 0.4 - pow( dot( eyeDirection, normal ), 0.9 ) );
	float4 rimLightColour = rimStrength * rimLightValue;
	
	oColor = lightDiffuse * Lit.y * dff + ambient * dff + rimLightColour;
	
	oColor = oColor*tex2D( textureModulate, Input.uv1)*modulate_factor;
	
	oColor.w=oColor.w*alpha_modulate;
	
	return oColor;
}
