#include "EHTestScene.h"
#include "EHObject.h"
#include "EHGameObject.h"
#include "EHMeshRenderer.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHCollisionManager.h"
#include "EHRigidbody.h"
#include "EHGround.h"

namespace EH
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		GameObject* testobject = Object::Instantiate<GameObject>(enums::eLayerType::Player);

		MeshRenderer* temp = testobject->AddComponent<MeshRenderer>();
		temp->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		temp->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		Transform* tr = testobject->AddComponent<Transform>();
		tr->SetPosition(Math::Vector3(0.f, 0.5f, 0.f));

		Collider* col = testobject->AddComponent<Collider>();
		col->SetScale(Math::Vector3(0.2f, 0.2f, 0.f));

		Rigidbody* rigid = testobject->AddComponent<Rigidbody>();

		Player* script = new Player();
		testobject->SetScript(script);

		GameObject* testobject2 = Object::Instantiate<GameObject>(enums::eLayerType::Bullet);

		temp = testobject2->AddComponent<MeshRenderer>();
		temp->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		temp->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		tr = testobject2->AddComponent<Transform>();
		tr->SetPosition(Math::Vector3(0.f, -0.5f, 0.f));

		col = testobject2->AddComponent<Collider>();
		col->SetScale(Math::Vector3(1.f, 0.5f, 0.f));

		Ground* script2 = new Ground();
		testobject2->SetScript(script2);

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Bullet,true);
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}
}