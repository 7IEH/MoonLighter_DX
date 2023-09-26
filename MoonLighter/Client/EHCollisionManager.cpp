#include "EHCollisionManager.h"
#include "EHSceneManager.h"
#include "EHScene.h"

namespace EH
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<(UINT)enums::eLayerType::End> CollisionManager::mLayersMasks[(UINT)enums::eLayerType::End] = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* curscene = SceneManager::GetCurScene();
		for (UINT row = 0;row < (UINT)enums::eLayerType::End;row++)
		{
			for (UINT col = 0;col < (UINT)enums::eLayerType::End;col++)
			{
				if (mLayersMasks[row][col])
				{
					LayerCollision(curscene, enums::eLayerType(row), enums::eLayerType(col));
				}
			}
		}
	}

	void CollisionManager::Render()
	{
	}

	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mLayersMasks->reset();
	}

	void CollisionManager::CollisionLayerCheck(enums::eLayerType left, enums::eLayerType right, bool enable)
	{
		int row = -1;
		int col = -1;

		if ((UINT)left > (UINT)right)
		{
			row = (UINT)right;
			col = (UINT)left;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}
		mLayersMasks[row][col] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene, enums::eLayerType left, enums::eLayerType right)
	{
		std::vector<GameObject*> leftobjects = scene->GetLayer(left).GetObjects();
		std::vector<GameObject*> rightobjects = scene->GetLayer(right).GetObjects();

		for (GameObject* leftobj : leftobjects)
		{
			Collider* leftcol = leftobj->GetComponent<Collider>();
			if (leftcol == nullptr)
				continue;
			for (GameObject* rightobj : rightobjects)
			{
				if (leftobj == rightobj)
					continue;
				Collider* rightcol = rightobj->GetComponent<Collider>();
				if (rightcol == nullptr)
					continue;
				ColliderCollision(leftcol, rightcol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		ColliderID id = {};
		id.left = (UINT)left;
		id.right = (UINT)right;

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		// 현재 충돌
		if (Intersect(left, right))
		{
			if (iter->second)
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
			else
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
		}
		// 현재 충돌 안하는중
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
	/*	if (!left->GetEnabled() || !right->GetEnabled())
		{
			return false;
		}*/

		Math::Vector3 leftpos = left->GetOwner()->GetComponent<Transform>()->GetPosition();
		Math::Vector3 leftscale = left->GetScale();
		Math::Vector3 rightpos = right->GetOwner()->GetComponent<Transform>()->GetPosition();
		Math::Vector3 rightscale = right->GetScale();
					
		Math::Vector3 leftoffset = left->GetOffset();
		Math::Vector3 rightoffset = right->GetOffset();

		if (fabs((leftpos.x + leftoffset.x) - (rightpos.x + rightoffset.x)) <= fabs(leftscale.x / 2.f + rightscale.x / 2.f)
			&& fabs((leftpos.y + leftoffset.y) - (rightpos.y + rightoffset.y)) <= fabs(leftscale.y / 2.f + rightscale.y / 2.f))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}