//---- VERTEX PROGRAM DECLARATIONS

float4x4 matViewProjection;

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

sampler blending_texture : register(s0);
      //BASE
// alpha map
sampler  base_alphaMapSampler : register(s1);

// layer 0 texture
sampler  base_layer0Sampler : register(s2);

// layer 1 texture
sampler  base_layer1Sampler : register(s3);

// layer 2 texture
sampler  base_layer2Sampler : register(s4);

// layer 3 texture
sampler  base_layer3Sampler : register(s5);

sampler texture_normal_base : register(s6);

sampler modulate_color_base : register(s7);

      //BLENDED
// alpha map
sampler  blended_alphaMapSampler : register(s8);

// layer 0 texture
sampler  blended_layer0Sampler : register(s9);

// layer 1 texture
sampler  blended_layer1Sampler : register(s10);

// layer 2 texture
sampler  blended_layer2Sampler : register(s11);

// layer 3 texture
sampler  blended_layer3Sampler : register(s12);

sampler texture_normal_blended : register(s13);

sampler modulate_color_blended : register(s14);

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

float2 calculateUV(float2 uv,float3 scroll,float3 tiling)
{
    uv.x = uv.x*tiling.x; 
    uv.y = uv.y*tiling.y;  
        
    uv.x=uv.x+scroll.x;
    uv.y=uv.y+scroll.y;

    return uv;
}

float4 calculateColor(
       float4 diffuse_color,
       float4 normal_color,
       float4 modulate_color,
       float4 normalIn, 
       float3 eyeDirection,
       float3 lightDirection, 
       float3 halfAngle, 
       float4 lightDiffuse,
       float4 ambient,
       float4 rimStrength
       )
{
    float4 normal;
    float NdotL;
    float NdotH;
    float4 Lit;
    float4 dff;
    float rimLightValue;
    float4 rimLightColour;
    float4 oColor;
    
	normal = normalize( normalIn * normal_color );

    NdotL = dot( lightDirection, normal );
	NdotH = dot( halfAngle, normal );
	Lit = lit( NdotL, NdotH, 0 );

	rimLightValue =  saturate( 0.4 - pow( dot( eyeDirection, normal ), 0.9 ) );
	rimLightColour = rimStrength * rimLightValue; 

 	oColor = lightDiffuse * Lit.y * diffuse_color + ambient * diffuse_color + rimLightColour;

    oColor = oColor*modulate_color;  
        
    return oColor;   
}

float4 calculateBaseDiffuseColor(
    in float2 uv,
    in float2 scale,
    in float4 alphaMask
    )
{
    float4 oColor;
    
    float4 alpha = tex2D(base_alphaMapSampler, uv);
 
    alpha = alpha * alphaMask;

    float4 l0 = tex2D(base_layer0Sampler, uv*scale);
    float4 l1 = tex2D(base_layer1Sampler, uv*scale);
    float4 l2 = tex2D(base_layer2Sampler, uv*scale);
    float4 l3 = tex2D(base_layer3Sampler, uv*scale);

    
    float sum = alpha.r + alpha.g +alpha.b +alpha.a;
 
    oColor = (alpha.r * l0 + alpha.g * l1 + alpha.b * l2 + alpha.a * l3)/sum;
 
    return oColor;   
}

float4 calculateBlendedDiffuseColor(
    in float2 uv,
    in float2 scale,
    in float4 alphaMask
    )
{
    float4 oColor;
    
    float4 alpha = tex2D(blended_alphaMapSampler, uv);
 
    alpha = alpha * alphaMask;

    float4 l0 = tex2D(blended_layer0Sampler, uv*scale);
    float4 l1 = tex2D(blended_layer1Sampler, uv*scale);
    float4 l2 = tex2D(blended_layer2Sampler, uv*scale);
    float4 l3 = tex2D(blended_layer3Sampler, uv*scale);

    
    float sum = alpha.r + alpha.g +alpha.b +alpha.a;
 
    oColor = (alpha.r * l0 + alpha.g * l1 + alpha.b * l2 + alpha.a * l3)/sum;
 
    return oColor;   
}

//------ FRAGMENT PROGRAMS

float3 displacement;
float3 scroll_blending;
float3 scroll_animation;
float mix_factor;
float blending;
float3 tiling;
float3 blending_tiling;
float time_elapsed;
float modulate_factor;
float alpha_modulate;
float4 lightDiffuse_base;
float4 ambient_base;
float4 rimStrength_base;
float4 lightDiffuse_blended;
float4 ambient_blended;
float4 rimStrength_blended;

uniform float2 base_scale;
uniform float4 base_alphaMask;

uniform float2 blended_scale;
uniform float4 blended_alphaMask;

float4 main_fp(PS_INPUT Input) : COLOR0
{
    float4 erosion_info;
    float4 base_color;
    float4 blended_color;
    float normalized_blending_factor;  
    float2 original_uv;
    float4 oColor;

    original_uv=Input.uv;
    
    Input.uv=calculateUV(Input.uv,-scroll_animation*time_elapsed,tiling);
    Input.uv1=calculateUV(Input.uv1,-scroll_animation*time_elapsed,tiling);
    erosion_info=tex2D(blending_texture,calculateUV(Input.uv,displacement-scroll_blending*time_elapsed,blending_tiling)); 

    float3 eyeDirection = normalize( Input.eyePosition - Input.positionIn.xyz );
    float3 lightDirection = normalize( Input.lightPosition.xyz - ( Input.positionIn * Input.lightPosition.w ).xyz );
    float3 halfAngle = normalize( lightDirection + eyeDirection );
    
    float4 base_diffuse= calculateBaseDiffuseColor(Input.uv1,base_scale,base_alphaMask);
    float4 blended_diffuse= calculateBlendedDiffuseColor(Input.uv1,blended_scale,blended_alphaMask);
    
    base_color=    calculateColor(base_diffuse,   tex2D(texture_normal_base,Input.uv),    float4(1,1,1,1)*(1-modulate_factor)+tex2D( modulate_color_base,original_uv)*modulate_factor,   Input.normalIn, eyeDirection,lightDirection, halfAngle, lightDiffuse_base,ambient_base,rimStrength_base);
    blended_color= calculateColor(blended_diffuse,tex2D(texture_normal_blended,Input.uv), float4(1,1,1,1)*(1-modulate_factor)+tex2D( modulate_color_blended,original_uv)*modulate_factor,Input.normalIn, eyeDirection,lightDirection, halfAngle, lightDiffuse_blended,ambient_blended,rimStrength_blended);

    normalized_blending_factor=(erosion_info.x-(mix_factor-blending))/(2*blending);
	
    if(erosion_info.x>=mix_factor+blending || mix_factor==0.0f)
    {
        oColor = base_color;
    }
    else if(erosion_info.x<=mix_factor-blending || mix_factor==1.0f)
    {
        oColor = blended_color;
    }   
    else
    {       
        oColor=normalized_blending_factor* base_color+(1-normalized_blending_factor)*blended_color; 
    }
    
	oColor.w=oColor.w*alpha_modulate;
	
	return oColor;
}
