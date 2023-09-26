#include "EHCollider.h"
#include "EHGameObject.h"

namespace EH
{
	Collider::Collider()
		:
		  Component(enums::eCommponentType::Collider)
		, mScale(Math::Vector3(0.f,0.f,0.f))
		, mOffset(Math::Vector3(0.f,0.f,0.f))
		, mAffectedCamera(true)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::Render()
	{
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
	}
}