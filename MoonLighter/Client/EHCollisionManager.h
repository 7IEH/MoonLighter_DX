#pragma once
#include "Commoninclude.h"
#include "EHCollider.h"


namespace EH
{
	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render();

		static void Clear();
		static void CollisionLayerCheck(enums::eLayerType left, enums::eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, enums::eLayerType left, enums::eLayerType right);
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<(UINT)enums::eLayerType::End> mLayersMasks[(UINT)enums::eLayerType::End];
	};
}


