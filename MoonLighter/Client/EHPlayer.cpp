#include "EHPlayer.h"
#include "EHApplication.h"
#include "EHTransform.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHGameObject.h"
#include "EHObject.h"
#include "EHMeshRenderer.h"
#include "EHResources.h"
#include "EHScript.h"

extern EH::Application application;

namespace EH
{
	Player::Player()
	{
	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
	}

	void Player::Update()
	{
		Math::Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Math::Vector3 scale = GetOwner()->GetComponent<Transform>()->GetScale();
		if (Input::Getkey(eKeyCode::W).state == eKeyState::PRESSED)
		{
			pos.y += 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			pos.y -= 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			pos.x -= 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			pos.x += 1.f * Time::GetDeltaTime();
			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}

		if (Input::Getkey(eKeyCode::Q).state == eKeyState::PRESSED)
		{
			scale.x += 0.1f;
			scale.y += 0.1f;
			GetOwner()->GetComponent<Transform>()->SetScale(scale);
		}

		if (Input::Getkey(eKeyCode::E).state == eKeyState::PRESSED)
		{
			scale.x -= 0.1f;
			scale.y -= 0.1f;
			GetOwner()->GetComponent<Transform>()->SetScale(scale);
		}	
	}

	void Player::FixedUpdate()
	{

	}

	void Player::Render()
	{

	}

}