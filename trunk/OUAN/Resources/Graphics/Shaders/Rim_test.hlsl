float4x4 matViewProjection;
float4x4 matView;

struct VS_INPUT 
{
   float4 Position : POSITION;
   float2 Texcoord : TEXCOORD0;
   float3 Normal: NORMAL;
   
};

struct VS_OUTPUT 
{
   float4 Position : POSITION;
   float2 Texcoord : TEXCOORD0;
   float3 VertexPosition: TEXCOORD1;
   float3 Normal: TEXCOORD2;
   
   
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( matViewProjection,Input.Position);
   Output.Texcoord = Input.Texcoord;
   Output.VertexPosition = mul(matView,Input.Position);
   Output.Normal = Input.Normal;  
   return( Output );
   
}

sampler baseMap: register(s0);
float4 eyePosition;

struct PS_INPUT 
{
   float2 Texcoord : TEXCOORD0;
   float3  Position: TEXCOORD1;
   float3 Normal: TEXCOORD2;
};

float4 ps_main( PS_INPUT Input ) : COLOR0
{
   float3 n = normalize(Input.Normal);
   float3 eyeDir = normalize(eyePosition.xyz-Input.Position.xyz);
   
   float4 outColor=tex2D( baseMap, Input.Texcoord );
   
   outColor += 1-(max(dot(eyeDir.xyz,n),-0.3));
   return outColor;
   
}
