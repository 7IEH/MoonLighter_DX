#include "EHMesh.h"
#include "EHGraphicDevice.h"
#include "EHRenderer.h"

namespace EH
{
	Mesh::Mesh()
		: mbufferType(buffertype::None)
	{
	}

	Mesh::~Mesh()
	{
	}

	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Mesh::CreateVertexBuffer(void* data, UINT Count, unsigned long long size)
	{
		mIndexCount = Count;
		mVBDesc.ByteWidth = size * Count;
		mVBDesc.Usage = D3D11_USAGE_IMMUTABLE;
		mVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA SubData = {};
		SubData.pSysMem = data;

		if (FAILED(GetDevice()->GetGPUDevice()->CreateBuffer(&mVBDesc, &SubData, mVertexBuffer.GetAddressOf())))
			return false;

		return true;
	}

	void Mesh::BindBuffer()
	{
		if (mbufferType == buffertype::Vertex)
		{
			UINT stride = sizeof(renderer::Vertex);
			UINT offset = 0;
			GetDevice()->GetGPUContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		}
		else if (mbufferType == buffertype::Texture)
		{
			UINT stride = sizeof(renderer::TextureVertex);
			UINT offset = 0;
			GetDevice()->GetGPUContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		}
	}

	void Mesh::Render()
	{
		BindBuffer();
		GetDevice()->GetGPUContext()->Draw(mIndexCount, 0);
	}
}