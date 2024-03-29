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

			// 1. pFileName : 쉐이더 정보가 담긴 hlsl 파일 이름
			// 2. pDefines : 셰이더 매크로를 정의하는 D3D_SHADER_MACRO 구조 의 선택적 배열입니다 .
			// 3. pInclude : 컴파일러가 포함 파일을 처리하는 데 사용하는 ID3DInclude 인터페이스 에 대한 선택적 포인터입니다.
			// 4. pEntrypoint : shader에서 진입 지점을 정해줍니다. shader에도 진입 지점이 많기 때문
			// 5. pTarget : shader의 사용할 프로그램 버전을 지정해줍니다.
			// 6. Flags1 : hlsl 파일을 컴파일 하는 방법을 지정해줍니다.
			// 7. Flags2 : 효과 컴파일 옵션 의 조합입니다.
			// 8. ppCode : 쉐이더 정보를 담은 구조체를 반환합니다.
			// 9. ppErrorMags: blob 생성에 있어 error 발생 시 error 정보를 byte 구조체로 반환합니다.

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
			// 해당 vertex option를 가진 vertex shader를 생성합니다.
			// 1. pShaderBytecode : 컴파일된 셰이더에 대한 포인터입니다.
			// 2. BytecodeLength : 컴파일된 꼭짓점 셰이더의 크기입니다.
			// 3. ID3D11ClassLinkage* : 클래스 연결 인터페이스에 대한 포인터입니다.
			// 4. ID3D11VertexShader** : 생성된 vertexshader를 반환합니다.

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
		// 스크래치 이미지 생성.
		DirectX::ScratchImage image;
		HRESULT result = DirectX::LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, NULL, image);

		// 오류 검사.
		if (FAILED(result))
		{
			MessageBox(nullptr, L"스크래치 이미지 로드 실패", L"오류", 0);
			//throw std::exception("스크래치 이미지 로드 실패");
			return;
		}

		// 텍스쳐 생성.
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		result = DirectX::CreateTexture(
			GetDevice()->GetGPUDevice().Get(),
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			(ID3D11Resource**)texture.GetAddressOf()
		);

		// 오류 검사.
		if (FAILED(result))
		{
			MessageBox(nullptr, L"텍스처 생성 실패", L"오류", 0);
			//throw std::exception("텍스처 생성 실패");
			return;
		}

		// 쉐이더 리소스 뷰 생성.
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

		// 오류 검사.
		if (FAILED(result))
		{
			MessageBox(nullptr, L"셰이더 리소스 뷰 생성 실패", L"오류", 0);
			//throw std::exception("셰이더 리소스 뷰 생성 실패");
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