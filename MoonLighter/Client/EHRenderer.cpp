#include "EHRenderer.h"
#include "EHResources.h"
#include "EHGraphicDevice.h"
#include "EHResources.h"


namespace EH::renderer
{
	D3D11_INPUT_ELEMENT_DESC InputLayouts[2];
	Mesh* mesh = nullptr;
	Mesh* mesh1 = nullptr;
	Mesh* texturemesh = nullptr;

	Shader* shader = nullptr;
	Shader* textureshader = nullptr;
	ConstantBuffer* constantBuffers[(UINT)enums::CBYTES::END];

	void LoadBuffer()
	{
		std::vector<Vertex> vertexes;
		vertexes.resize(6);
		vertexes[0].pos = Math::Vector3(0.1f, 0.1f, 0.f);
		vertexes[0].Color = Math::Vector4(1.f, 0.f, 0.f, 0.f);

		vertexes[1].pos = Math::Vector3(0.1f, -0.1f, 0.f);
		vertexes[1].Color = Math::Vector4(0.f, 1.f, 0.f, 0.f);

		vertexes[2].pos = Math::Vector3(-0.1f, 0.1f, 0.f);
		vertexes[2].Color = Math::Vector4(0.f, 0.f, 1.f, 0.f);

		vertexes[3].pos = Math::Vector3(0.1f, -0.1f, 0.f);
		vertexes[3].Color = Math::Vector4(1.f, 0.f, 0.f, 0.f);

		vertexes[4].pos = Math::Vector3(-0.1f, -0.1f, 0.f);
		vertexes[4].Color = Math::Vector4(0.f, 1.f, 0.f, 0.f);

		vertexes[5].pos = Math::Vector3(-0.1f, 0.1f, 0.f);
		vertexes[5].Color = Math::Vector4(0.f, 0.f, 1.f, 0.f);

		/*std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);*/

		mesh->CreateVertexBuffer(vertexes.data(), 6 ,sizeof(Vertex));
		Resources::Insert(L"TriangleMesh", mesh);

		vertexes[0].pos = Math::Vector3(0.f, 0.1f, 0.F);
		vertexes[0].Color = Math::Vector4(1.f, 0.f, 0.f, 0.f);

		vertexes[1].pos = Math::Vector3(0.1f, -0.1f, 0.f);
		vertexes[1].Color = Math::Vector4(0.f, 1.f, 0.f, 0.f);

		vertexes[2].pos = Math::Vector3(-0.1f, -0.1f, 0.f);
		vertexes[2].Color = Math::Vector4(0.f, 0.f, 1.f, 1.f);

		/*std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);*/

		mesh1->CreateVertexBuffer(vertexes.data(), 3, sizeof(Vertex));
		Resources::Insert(L"BulletMesh", mesh1);

		std::vector<TextureVertex> texturevertex;
		texturevertex.resize(6);

		texturevertex[0].pos = Math::Vector3(0.1f, 0.1f, 0.f);
		texturevertex[0].uv = Math::Vector2(1.f,0.f);

		texturevertex[1].pos = Math::Vector3(0.1f, -0.1f, 0.f);
		texturevertex[1].uv = Math::Vector2(1.f,1.f);

		texturevertex[2].pos = Math::Vector3(-0.1f, 0.1f, 0.f);
		texturevertex[2].uv = Math::Vector2(0.f, 0.f);

		texturevertex[3].pos = Math::Vector3(0.1f, -0.1f, 0.f);
		texturevertex[3].uv = Math::Vector2(1.f, 1.f);

		texturevertex[4].pos = Math::Vector3(-0.1f, -0.1f, 0.f);
		texturevertex[4].uv = Math::Vector2(0.f,1.f);

		texturevertex[5].pos = Math::Vector3(-0.1f, 0.1f, 0.f);
		texturevertex[5].uv = Math::Vector2(0.f, 0.f);

		texturemesh->CreateVertexBuffer(texturevertex.data(), 6, sizeof(TextureVertex));
		Resources::Insert(L"TextureMesh", texturemesh);

		constantBuffers[(UINT)enums::CBYTES::Transform] = new ConstantBuffer();
		constantBuffers[(UINT)enums::CBYTES::Transform]->Create(sizeof(CBUFFER));
		constantBuffers[(UINT)enums::CBYTES::Transform]->SetType(enums::CBYTES::Transform);
	}

	void LoadShader()
	{
		shader->Create(graphics::ShaderStage::VS, L"TriangleVS.hlsl", "vs_main");
		shader->Create(graphics::ShaderStage::PS, L"TrianglePS.hlsl", "ps_main");
		Resources::Insert(L"TriangleShader", shader);

		textureshader->Create(graphics::ShaderStage::VS, L"TextureVS.hlsl", "vs_main");
		textureshader->Create(graphics::ShaderStage::PS, L"TexturePS.hlsl", "ps_main");
		textureshader->CreateSamplerState();
		textureshader->ResourceViewCreate(L"..\\Resources\\NPC_Commander0.png");
		Resources::Insert(L"TextureShader", textureshader);

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{"POS",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"COL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		HRESULT hResult = GetDevice()->GetGPUDevice().Get()->CreateInputLayout(
			inputElementDesc
			, ARRAYSIZE(inputElementDesc)
			, shader->GetVSCode()->GetBufferPointer()
			, shader->GetVSCode()->GetBufferSize()
			, shader->GetInputLayoutAddressOf());

		D3D11_INPUT_ELEMENT_DESC inputElementDesc2[] =
		{
			{"POS",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		hResult = GetDevice()->GetGPUDevice().Get()->CreateInputLayout(
			inputElementDesc2
			, ARRAYSIZE(inputElementDesc2)
			, textureshader->GetVSCode()->GetBufferPointer()
			, textureshader->GetVSCode()->GetBufferSize()
			, textureshader->GetInputLayoutAddressOf());

		assert(SUCCEEDED(hResult));
	}

	void Initialize()
	{
		mesh = new Mesh();
		mesh1 = new Mesh();
		texturemesh = new Mesh();

		shader = new Shader();
		textureshader = new Shader();

		LoadShader();
		LoadBuffer();
	}

	void Release()
	{
		delete mesh;
		delete shader;
	}
}