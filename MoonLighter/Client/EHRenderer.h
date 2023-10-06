#pragma once

#include "Commoninclude.h"
#include "EHMesh.h"
#include "EHShader.h"
#include "EHConstantBuffer.h"

namespace EH::renderer
{
	struct Vertex
	{
		Math::Vector3 pos;
		Math::Vector4 Color;
	};

	struct CBUFFER
	{
		Math::Vector3 pos;
		int pad1;
		Math::Vector3 scale;
		int pad2;
	};

	struct TextureVertex
	{
		Math::Vector3 pos;
		Math::Vector2 uv;
	};

	void Initialize();
	void Release();

	// Mesh
	extern Mesh* mesh;
	extern Mesh* mesh1;
	extern Mesh* texturemesh;

	// Shader
	extern Shader* shader;
	extern Shader* textureshader;

	extern ConstantBuffer* constantBuffers[];
}

