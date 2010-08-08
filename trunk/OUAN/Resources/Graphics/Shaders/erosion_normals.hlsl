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

VS_OUTPUT erosion_normalsVS
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

sampler blending_texture : register(s0);
sampler diffuse_color_base : register(s1);
sampler diffuse_color_blended : register(s2);
sampler modulate_color_base : register(s3);
sampler modulate_color_blended : register(s4);
sampler texture_normal_base : register(s5);
sampler texture_normal_blended : register(s6);

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


float4 erosion_normalsFS(PS_INPUT Input) : COLOR0
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
    
    base_color=    calculateColor(tex2D(diffuse_color_base,Input.uv1),   tex2D(texture_normal_base,Input.uv),    tex2D( modulate_color_base,original_uv)*modulate_factor,   Input.normalIn, eyeDirection,lightDirection, halfAngle, lightDiffuse_base,ambient_base,rimStrength_base);
    blended_color= calculateColor(tex2D(diffuse_color_blended,Input.uv1),tex2D(texture_normal_blended,Input.uv), tex2D( modulate_color_blended,original_uv)*modulate_factor,Input.normalIn, eyeDirection,lightDirection, halfAngle, lightDiffuse_blended,ambient_blended,rimStrength_blended);

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
