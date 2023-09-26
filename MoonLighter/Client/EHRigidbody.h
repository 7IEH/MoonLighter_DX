#pragma once

#include "Commoninclude.h"
#include "EHComponent.h"

namespace EH
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void Clear() { mForce = Math::Vector3(0.f, 0.f, 0.f); }

		void SetMass(float mass) { mfMass = mass; }
		void AddForce(Math::Vector3 force) { mForce += force; }

		void SetVeclocity(Math::Vector3 velocity) { mVelocity = velocity; }
		Math::Vector3 GetVelocity() { return mVelocity; }

		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }

		void SetFriction(float friction) { mfFriction = friction; }
		float GetFriction() { return mfFriction; }

	private:
		bool mbGround;

		float mfMass;
		float mfFriction;
		float mCoefficient;

		Math::Vector3 mVelocity;
		Math::Vector3 mAccelation;
		Math::Vector3 mForce;
		Math::Vector3 mGravity;
		Math::Vector3 mMaxGravity;
	};
}


