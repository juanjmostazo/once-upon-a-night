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

VS_OUTPUT main_vp
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


//Texture samplers
 
    // alpha map
    sampler  alphaMapSampler : register(s0);
 
    // layer 0 texture
    sampler  layer0Sampler : register(s1);
 
    // layer 1 texture
    sampler  layer1Sampler : register(s2);
 
    // layer 2 texture
    sampler  layer2Sampler : register(s3);
 
    // layer 3 texture
    sampler  layer3Sampler : register(s4);
    
    // normal texture
    sampler textureNormal : register(s5);
    
    //modulate texture
    sampler textureModulate : register(s6);
    
float4 calculateDiffuseColor(
    in float2 uv,
    in float2 scale,
    in float4 alphaMask
    )
{
    float4 oColor;
    
    float4 alpha = tex2D(alphaMapSampler, uv);
 
    alpha = alpha * alphaMask;

    float4 l0 = tex2D(layer0Sampler, uv*scale);
    float4 l1 = tex2D(layer1Sampler, uv*scale);
    float4 l2 = tex2D(layer2Sampler, uv*scale);
    float4 l3 = tex2D(layer3Sampler, uv*scale);

    
    float sum = alpha.r + alpha.g +alpha.b +alpha.a;
 
    oColor = (alpha.r * l0 + alpha.g * l1 + alpha.b * l2 + alpha.a * l3)/sum;
 
    return oColor;   
}
    
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
float2 scale;
float4 alphaMask;
    
float4 main_fp(PS_INPUT Input) : COLOR0
{
    float4 oColor;
	float3 eyeDirection = normalize( Input.eyePosition - Input.positionIn.xyz );
	float3 lightDirection = normalize( Input.lightPosition.xyz - ( Input.positionIn * Input.lightPosition.w ).xyz );
	float3 halfAngle = normalize( lightDirection + eyeDirection );
	
	float4 normal = normalize( Input.normalIn * tex2D( textureNormal, Input.uv ) );
	
	float NdotL = dot( lightDirection, normal );
	float NdotH = dot( halfAngle, normal );
	float4 Lit = lit( NdotL, NdotH, 0 );
	
	float4 dff = calculateDiffuseColor(Input.uv1,scale,alphaMask);
	
	float rimLightValue =  saturate( 0.4 - pow( dot( eyeDirection, normal ), 0.9 ) );
	float4 rimLightColour = rimStrength * rimLightValue;
	
	oColor = lightDiffuse * Lit.y * dff + ambient * dff + rimLightColour;
	
	oColor = oColor*(1-modulate_factor)+oColor*tex2D( textureModulate, Input.uv1)*modulate_factor;
	
	oColor.w=oColor.w*alpha_modulate;
	
	return oColor;
}
