#include "EHShader.h"
#include <filesystem>
#include "EHGraphicDevice.h"

namespace EH
{
	Shader::Shader()
		:
		mTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}

	Shader::~Shader()
	{
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Shader::CreateSamplerState()
	{
		{
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

			HRESULT hResult = GetDevice()->GetGPUDevice()->CreateSamplerState(&samplerDesc, &mSampleState);
			assert(SUCCEEDED(hResult));
		}
	}

	void Shader::Create(const graphics::ShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		/*std::filesystem::path path
			= std::filesystem::current_path().parent_path();
		path += "\\Shaders_SOURCE\\";

		std::wstring shaderPath(path);
		shaderPath += file;*/
		ID3DBlob* shaderCompileErrorBlob = nullptr;

		if (stage == graphics::ShaderStage::VS)
		{
			HRESULT hResult = D3DCompileFromFile(file.c_str(), nullptr, nullptr, funcName.c_str(), "vs_5_0", 0, 0, mVSBlob.GetAddressOf(), &shaderCompileErrorBlob);

			// 1. pFileName : ���̴� ������ ��� hlsl ���� �̸�
			// 2. pDefines : ���̴� ��ũ�θ� �����ϴ� D3D_SHADER_MACRO ���� �� ������ �迭�Դϴ� .
			// 3. pInclude : �����Ϸ��� ���� ������ ó���ϴ� �� ����ϴ� ID3DInclude �������̽� �� ���� ������ �������Դϴ�.
			// 4. pEntrypoint : shader���� ���� ������ �����ݴϴ�. shader���� ���� ������ ���� ����
			// 5. pTarget : shader�� ����� ���α׷� ������ �������ݴϴ�.
			// 6. Flags1 : hlsl ������ ������ �ϴ� ����� �������ݴϴ�.
			// 7. Flags2 : ȿ�� ������ �ɼ� �� �����Դϴ�.
			// 8. ppCode : ���̴� ������ ���� ����ü�� ��ȯ�մϴ�.
			// 9. ppErrorMags: blob ������ �־� error �߻� �� error ������ byte ����ü�� ��ȯ�մϴ�.

			if (FAILED(hResult))
			{
				const char* errorString = NULL;
				if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
					errorString = "Could not compile shader; file not found";
				else if (shaderCompileErrorBlob)
				{
					errorString = (const char*)shaderCompileErrorBlob->GetBufferPointer();
					shaderCompileErrorBlob->Release();
				}
				MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			}
			// �ش� vertex option�� ���� vertex shader�� �����մϴ�.
			// 1. pShaderBytecode : �����ϵ� ���̴��� ���� �������Դϴ�.
			// 2. BytecodeLength : �����ϵ� ������ ���̴��� ũ���Դϴ�.
			// 3. ID3D11ClassLinkage* : Ŭ���� ���� �������̽��� ���� �������Դϴ�.
			// 4. ID3D11VertexShader** : ������ vertexshader�� ��ȯ�մϴ�.

			hResult = GetDevice()->GetGPUDevice().Get()->CreateVertexShader(mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
			assert(SUCCEEDED(hResult));
		}

		if (stage == graphics::ShaderStage::PS)
		{
			HRESULT hResult = D3DCompileFromFile(file.c_str(), nullptr, nullptr, funcName.c_str(), "ps_5_0", 0, 0, mPSBlob.GetAddressOf(), &shaderCompileErrorBlob);

			if (FAILED(hResult))
			{
				const char* errorString = NULL;
				if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
					errorString = "Could not compile shader; file not found";
				else if (shaderCompileErrorBlob)
				{
					errorString = (const char*)shaderCompileErrorBlob->GetBufferPointer();
					shaderCompileErrorBlob->Release();
				}
				MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			}

			hResult = GetDevice()->GetGPUDevice().Get()->CreatePixelShader
			(
				mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize()
				, nullptr
				, &mPS
			);
			assert(SUCCEEDED(hResult));
		}
	}

	void Shader::ResourceViewCreate(std::wstring filename)
	{
		// ��ũ��ġ �̹��� ����.
		DirectX::ScratchImage image;
		HRESULT result = DirectX::LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, NULL, image);

		// ���� �˻�.
		if (FAILED(result))
		{
			MessageBox(nullptr, L"��ũ��ġ �̹��� �ε� ����", L"����", 0);
			//throw std::exception("��ũ��ġ �̹��� �ε� ����");
			return;
		}

		// �ؽ��� ����.
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		result = DirectX::CreateTexture(
			GetDevice()->GetGPUDevice().Get(),
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			(ID3D11Resource**)texture.GetAddressOf()
		);

		// ���� �˻�.
		if (FAILED(result))
		{
			MessageBox(nullptr, L"�ؽ�ó ���� ����", L"����", 0);
			//throw std::exception("�ؽ�ó ���� ����");
			return;
		}

		// ���̴� ���ҽ� �� ����.
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));

		srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		D3D11_TEXTURE2D_DESC textureDesc;
		texture->GetDesc(&textureDesc);

		srvDesc.Format = textureDesc.Format;

		ID3D11ShaderResourceView* shaderResourceView;
		result = GetDevice()->GetGPUDevice().Get()->CreateShaderResourceView(
			texture.Get(),
			&srvDesc,
			&mResourceView
		);

		// ���� �˻�.
		if (FAILED(result))
		{
			MessageBox(nullptr, L"���̴� ���ҽ� �� ���� ����", L"����", 0);
			//throw std::exception("���̴� ���ҽ� �� ���� ����");
			return;
		}
	}

	void Shader::Update()
	{
		GetDevice()->GetGPUContext().Get()->IASetPrimitiveTopology(mTopology);
		GetDevice()->GetGPUContext().Get()->IASetInputLayout(mInputLayout.Get());
		GetDevice()->GetGPUContext().Get()->VSSetShader(mVS.Get(), nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShader(mPS.Get(), nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShaderResources(0, 1, mResourceView.GetAddressOf());
		GetDevice()->GetGPUContext().Get()->PSSetSamplers(0, 1, &mSampleState);
	}
}