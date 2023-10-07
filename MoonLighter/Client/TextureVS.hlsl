
struct VS_Input
{
    float3 pos : POS;
    float2 uv : TEXCOORD;
};

struct VS_Output
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

cbuffer TRANSFORM : register(b0)
{
    float3 cbpos;
    int pad1;
    float3 cbscale;
    int pad2;
};

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.pos * cbscale.xyz, 1.f);
    output.position.xyz += cbpos.xyz;
    output.uv = input.uv;
    
    return output;
}