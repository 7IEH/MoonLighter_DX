#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Math::Vector3 CaculatePos(Math::Vector3 pos) { return pos - mDiffDistance; }
		static void SetLookAt(Math::Vector3 lookat) { mLookAt = lookat; }
		static Math::Vector3 GetLookAt() { return mLookAt; }

	private:
		static Math::Vector3 mResolution;
		static Math::Vector3 mLookAt;
		static Math::Vector3 mDiffDistance;
		static GameObject* mTarget;

	};
}

