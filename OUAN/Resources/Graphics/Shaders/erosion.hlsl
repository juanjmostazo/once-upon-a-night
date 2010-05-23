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

struct PS_INPUT 
{
   float2 Texcoord : TEXCOORD0;
};

//------ FRAGMENT PROGRAMS

float4 erosionFS( PS_INPUT Input ) : COLOR0
{
	float4 outColour;
	float4 random=tex2D(tex2,Input.Texcoord);
	if (random.x>mix_factor)
		outColour=tex2D(tex0,Input.Texcoord);
	else
		outColour=tex2D(tex1,Input.Texcoord);
	return outColour;   
}

float4 erosionFS_2(
	PS_INPUT Input): COLOR0
{
	float4 outColour;
    float4 random=tex2D(tex2,Input.Texcoord*tiling);
    
    if(random.x>mix_factor+blending)
    {
       outColour=tex2D(tex0,Input.Texcoord);
    }
    else if(random.x<=mix_factor+blending && random.x>=mix_factor-blending)
    {
	   float normalized_blending_factor=(random.x-(mix_factor-blending))/(2*blending);
       outColour=normalized_blending_factor*tex2D(tex0,Input.Texcoord)+(1-normalized_blending_factor)*tex2D(tex1,Input.Texcoord); 
    }
    else
    {
       outColour=tex2D(tex1,Input.Texcoord);
    }
	return outColour;
}