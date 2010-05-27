//---- VERTEX PROGRAM DECLARATIONS

float4x4 matViewProjection;

struct VS_OUTPUT 
{
   float2 Texcoord : TEXCOORD0;
   float4 Position: POSITION;   
};

//---- VERTEX PROGRAM

VS_OUTPUT erosionVS(float4 Position: POSITION,
	float2 TexCoord: TEXCOORD0)
{
	VS_OUTPUT Output;
   Output.Position = mul( matViewProjection,Position);
   Output.Texcoord = TexCoord;
   return( Output );
}

//---- FRAGMENT PROGRAM DECLARATIONS

sampler tex0: register(s0);
sampler tex1: register(s1);
sampler tex2: register(s2);

float mix_factor;
float displacement;
float blending;
float tiling;
float3 scroll_blending;
float3 scroll_animation;

struct PS_INPUT 
{
   float2 Texcoord : TEXCOORD0;
};

// Auxiliary functions
float2 scrollUV (float2 uv, float2 scroll)
{
	float2 outUV=uv;
	outUV.x+=scroll.x;
	outUV.y+=scroll.y;
	return outUV;
}
float2 calculateUV(float2  uv, float3 scroll_animation)
{
	float2 outUV=scrollUV(uv, float2(scroll_animation.x, scroll_animation.y));
	
	return outUV;
}

float2 calculateBlendingTextureUV(float2 uv, float3 displacement, 
	float3 scroll_blending, float tiling)
{
	float2 outUV = scrollUV(uv, float2(scroll_blending.x+displacement.x,
		scroll_blending.y+displacement.y));
	outUV*=tiling;
	
	return outUV;
}

//------ FRAGMENT PROGRAMS

float4 erosionFS( PS_INPUT Input ) : COLOR0
{	
	float4 out_colour;
	float2 uv=calculateUV(Input.Texcoord,scroll_animation);
	
	float4 erosion_info=tex2D(tex2, calculateBlendingTextureUV(uv,displacement,
		scroll_blending,tiling));
		
	if (erosion_info.x>=mix_factor+blending || mix_factor==0.0f)
		out_colour=tex2D(tex0,uv);
	else if (erosion_info.x<=mix_factor-blending || mix_factor== 1.0f)
		out_colour=tex2D(tex1,uv);
	else
	{
		float normalized_blending_factor=(erosion_info.x  - (mix_factor-blending))/(2*blending);
		out_colour=normalized_blending_factor*tex2D(tex0,uv)+(1-normalized_blending_factor)*tex2D(tex1,uv);
	}	
	return out_colour;
}

float4 erosion_transparentFS(
	PS_INPUT Input): COLOR0
{
	float4 outColour;
	
	float2 uv= calculateUV(Input.Texcoord,scroll_animation);
	float4 erosion_info = tex2D (tex2, calculateBlendingTextureUV(uv,displacement,
		scroll_blending,tiling));
		
	outColour = tex2D(tex0,uv);	
	float4 tempColour = outColour;
	
	if (erosion_info.x>=mix_factor+blending || mix_factor==0.0f)
	{
		tempColour.w=1.0f;
	}
	else if (erosion_info.x<=mix_factor-blending || mix_factor==1.0f)
	{
		tempColour.w=0.0f;
	}
	else
	{
		tempColour.w= (erosion_info.x-(mix_factor-blending))/(2*blending);
	}
    if (outColour.w>tempColour.w)
	{
		outColour.w=tempColour.w;
	}
	return outColour;
}