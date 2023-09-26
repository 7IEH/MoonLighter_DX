#include "EHGameObject.h"
#include "EHGraphicDevice.h"
#include "EHObject.h"
#include "EHApplication.h"
#include "EHPlayer.h"
#include "EHGround.h"
#include "EHRigidbody.h"
#include "EHCollider.h"
#include "EHTransform.h"

extern EH::Application application;

namespace EH
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		if (mScript != nullptr)
			mScript->FixedUpdate();
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		if(mScript!=nullptr)
			mScript->Update();
		/*GetDevice()->GetGPUContext().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		GetDevice()->GetGPUContext().Get()->IASetInputLayout(mInputLayout);
		GetDevice()->GetGPUContext().Get()->VSSetShader(mVertexShader, nullptr, 0);
		GetDevice()->GetGPUContext().Get()->PSSetShader(mPixelShader, nullptr, 0);*/
	}

	void GameObject::Render()
	{

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}


		if (mScript != nullptr)
			mScript->Render();
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{

		// Çý±Ù¼±»ý´Ô ÄÚµå
		/*	for (Component* comp : mComponents)
			{
				if (comp == nullptr)
					continue;

				comp->OnCollisionEnter(other);
			}*/

		Player* player = dynamic_cast<Player*>(other->GetOwner()->GetScript());
		if (player != nullptr)
		{
			Transform* playertr = player->GetOwner()->GetComponent<Transform>();
			Transform* floortr = GetComponent<Transform>();

			Collider* playercol = player->GetOwner()->GetComponent<Collider>();
			Collider* floorcol = GetComponent<Collider>();

			if (player->GetOwner()->GetComponent<Rigidbody>()->GetVelocity().y < 0)
			{
				player->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);


				float scale = fabs(playercol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
				float len = fabs(playertr->GetPosition().y + playercol->GetOffset().y + -floortr->GetPosition().y);

				if (len < scale)
				{
					Math::Vector3 playerPos = playertr->GetPosition();
					playerPos.y += (scale - len) + 0.01f;
					playertr->SetPosition(playerPos);
				}
			}
		}
	}

	void GameObject::OnCollisionStay(Collider* other)
	{

	}

	void GameObject::OnCollisionExit(Collider* other)
	{

	}
}