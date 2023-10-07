#pragma once

#include "EHResource.h"

namespace EH
{
	enum class buffertype
	{
		  Vertex
		, Texture
		, None
	};

	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT Count, unsigned long long size);

		void BindBuffer();
		void Render();

		void SetBufferType(buffertype buffertype) { mbufferType = buffertype; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVBDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIBDesc;
		UINT mIndexCount;

		// 이후 삭제
		buffertype mbufferType;
	};
}


