#pragma once

#include "Commoninclude.h"
#include "EHComponent.h"

namespace EH
{
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetScale(Math::Vector3 scale) { mScale = scale; }
		Math::Vector3 GetScale() { return mScale; }

		Math::Vector3 SetAffectedCamera(bool affectedcamera) { mAffectedCamera = affectedcamera; }

		void SetOffset(Math::Vector3 offset) { mOffset = offset; }
		Math::Vector3 GetOffset() { return mOffset; }

	private:
		Math::Vector3 mScale;
		Math::Vector3 mOffset;
		bool mbisCollision;
		bool mAffectedCamera;
	};
}


