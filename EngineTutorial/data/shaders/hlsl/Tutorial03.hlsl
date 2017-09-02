struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer MyBuffer : register(b0)
{
	float4 instanceColor;
}

cbuffer MyBuffer2 : register(b1)
{
	float4x4 ProjectionViewWorldMatrix;
}


VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(position,ProjectionViewWorldMatrix);
    output.color = color + instanceColor;

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}