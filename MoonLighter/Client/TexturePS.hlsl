SamplerState SampleType;
Texture2D shaderTexture;

struct VS_Output
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 ps_main(VS_Output input) : SV_TARGET
{
    float4 color = shaderTexture.Sample(SampleType, input.uv);
   
    return color;
}

  //float4 textureColor;
    
    //textureColor = shaderTexture.Sample(SampleType, input.tex);

// pixel shader가 하는일 색깔에 대해 리턴 해줍니다.
// 색깔과 관련된 데이터만 처리 가능