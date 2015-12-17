cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer ReflectionBuffer
{
	matrix reflectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 reflectionPosition : TEXCOORD1;
};

PixelInputType ReflectionVertexShader(VertexInputType input)
{
	PixelInputType output;
	matrix reflectProjectWorld;

	//Change the position vector to be 4 units from proper matrix calculations
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//Store the texture coorfinates for the pixel shader
	output.tex = input.tex;

	//Create the reflection projection worl matrix
	reflectProjectWorld = mul(reflectionMatrix, projectionMatrix);
	reflectProjectWorld = mul(worldMatrix, reflectProjectWorld);

	//Calculate the input position agaisnt the reflectProjectWorld matrix
	output.reflectionPosition = mul(input.position, reflectProjectWorld);

	return output;
}