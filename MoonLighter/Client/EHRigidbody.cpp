#include "EHRigidbody.h"
#include "EHTime.h"
#include "EHTransform.h"
#include "EHGameObject.h"

namespace EH
{
	Rigidbody::Rigidbody()
		:
		Component(enums::eCommponentType::Rigidbody)
		, mfMass(1.f)
		, mVelocity(Math::Vector3(0.f, 0.f, 0.f))
		, mAccelation(Math::Vector3(0.f, 0.f, 0.f))
		, mForce(Math::Vector3(0.f, 0.f, 0.f))
		, mfFriction(0.001f)
		, mCoefficient(0.002f)
		, mbGround(false)
	{
		mGravity = Math::Vector3(0.f, 0.1f);
		mMaxGravity = Math::Vector3(0.2f, 1.f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		mAccelation = mForce / mfMass;

		mVelocity += Math::Vector3(mAccelation.x * Time::GetDeltaTime(), mAccelation.y * Time::GetDeltaTime());

		if (mbGround)
		{
			Math::Vector3 gravity = mGravity;
			gravity.Normalized();
			float dot = Math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity -= Math::Vector3(mGravity.x * Time::GetDeltaTime(), mGravity.y * Time::GetDeltaTime() , mGravity.z * Time::GetDeltaTime());
		}

		Math::Vector3 gravity = mGravity;
		gravity.Normalized();
		float dot = Math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Math::Vector3 SideGravity = mVelocity - gravity;
		if (mMaxGravity.y < gravity.Length())
		{
			gravity.Normalized();
			gravity.y *= mMaxGravity.y;
		}

		if (mMaxGravity.x < SideGravity.Length())
		{
			SideGravity.Normalized();
			SideGravity.x *= mMaxGravity.x;
		}
		mVelocity = gravity + SideGravity;

		if (!(mVelocity == Math::Vector3(0.f, 0.f, 0.f)))
		{
			Math::Vector3 friction = -mVelocity;
			friction = friction.Normalized() * mfFriction * mfMass * Time::GetDeltaTime();

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Math::Vector3(0.f, 0.f);
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(tr->GetPosition() + Math::Vector3(mVelocity.x * Time::GetDeltaTime(), mVelocity.y * Time::GetDeltaTime(), mVelocity.z * Time::GetDeltaTime()));
		Clear();
	}

	void Rigidbody::Render()
	{
	}
}