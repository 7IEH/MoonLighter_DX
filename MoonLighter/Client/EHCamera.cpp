#include "EHCamera.h"
#include "EHApplication.h"
#include "EHSceneManager.h"
#include "EHInput.h"
#include "EHTime.h"

extern EH::Application application;


namespace EH
{
	Math::Vector3 Camera::mResolution = {};
	Math::Vector3 Camera::mLookAt = {};
	Math::Vector3 Camera::mDiffDistance = {};
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
	/*	mResolution.x = 1600;
		mResolution.y = 900;*/

		mLookAt.x = 0.f;
		mLookAt.y = 0.f;
		mLookAt.z = 0.f;
	}

	void Camera::Update()
	{
		if (Input::Getkey(eKeyCode::LEFT).state == eKeyState::PRESSED)
		{
			mLookAt.x -= 1.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::UP).state == eKeyState::PRESSED)
		{
			mLookAt.y += 1.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::DOWN).state == eKeyState::PRESSED)
		{
			mLookAt.y -= 1.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::RIGHT).state == eKeyState::PRESSED)
		{
			mLookAt.x += 1.f * Time::GetDeltaTime();
		}

		/*if (mTarget)
		{
			mLookAt = mTarget->GetComponent<Transform>()->Getpos();
		}*/

		//if (mLookAt.x < 640.f)
		//{
		//	mLookAt.x = 640.f;
		//}

		//if (mLookAt.y < 360.f)
		//{
		//	mLookAt.y = 360.f;
		//}

		//if (mLookAt.x > SceneManager::GetCurScene()->GetSize().x - 640.f)
		//{
		//	mLookAt.x = SceneManager::GetCurScene()->GetSize().x - 640.f;
		//}

		//if (mLookAt.y > SceneManager::GetCurScene()->GetSize().y - 360.f)
		//{
		//	mLookAt.y = SceneManager::GetCurScene()->GetSize().y - 360.f;
		//}

		mDiffDistance = mLookAt - Math::Vector3(0.f,0.f,0.f);
	}

}
