#pragma once

#include "Commoninclude.h"
#include "EHComponent.h"
#include "EHTransform.h"
#include "EHScript.h"

namespace EH
{
	/*class CollisionEvent
	{
	protected:
		virtual void OnCollisionEnter(class Collider* other) {}
		virtual void OnCollisionStay(class Collider* other) {}
		virtual void OnCollisionExit(class Collider* other) {}
	};*/

	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void Render();

		void OnCollisionEnter(class Collider* other);
		void OnCollisionStay(class Collider* other);
		void OnCollisionExit(class Collider* other);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			mComponents.push_back(comp);
			comp->SetOwenr(this);
			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* temp = nullptr;
			for (Component* comp : mComponents)
			{
				temp = dynamic_cast<T*>(comp);
				if (temp != nullptr)
					return temp;
			}
			return temp;
		}

		void SetScript(Script* script)
		{
			mScript = script;
			mScript->SetOwenr(this);
		}

		Script* GetScript() { return mScript; }

	private:
		std::vector<Component*> mComponents;
		Script* mScript;
	};
}


