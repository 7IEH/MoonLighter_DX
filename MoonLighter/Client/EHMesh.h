#pragma once

#include "EHResource.h"

namespace EH
{
	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT Count);

		void BindBuffer();
		void Render();

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVBDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIBDesc;
		UINT mIndexCount;
	};
}


