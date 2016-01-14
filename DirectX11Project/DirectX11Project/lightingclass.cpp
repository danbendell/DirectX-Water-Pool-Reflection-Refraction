#include "LightingClass.h"

LightingClass::LightingClass() {}

LightingClass::LightingClass(const LightingClass& other) {}

LightingClass::~LightingClass() {}

void LightingClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightingClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightingClass::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
	return;
}

void LightingClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightingClass::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}

D3DXVECTOR4 LightingClass::GetAmbientColor()
{
	return m_ambientColor;
}

D3DXVECTOR4 LightingClass::GetDiffuseColor()
{
	return m_diffuseColor;
}

D3DXVECTOR3 LightingClass::GetDirection()
{
	return m_direction;
}

D3DXVECTOR4 LightingClass::GetSpecularColor()
{
	return m_specularColor;
}

float LightingClass::GetSpecularPower()
{
	return m_specularPower;
}