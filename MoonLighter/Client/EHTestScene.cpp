#include "EHTestScene.h"
#include "EHObject.h"
#include "EHGameObject.h"
#include "EHMeshRenderer.h"
#include "EHResources.h"
#include "EHPlayer.h"

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

		Player* script = new Player();
		testobject->SetScript(script);

		GameObject* testobject2 = Object::Instantiate<GameObject>(enums::eLayerType::Bullet);

		temp = testobject2->AddComponent<MeshRenderer>();
		temp->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		temp->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		tr = testobject2->AddComponent<Transform>();
		tr->SetPosition(Math::Vector3(2.f, 2.f, 0.f));
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