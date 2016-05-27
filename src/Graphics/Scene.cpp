#include "Scene.h"

#include "Objects/CubeMap.h"
#include "Objects/Cube.h"
#include "Objects/Egg.h"
#include "Objects/Chicken.h"
#include "Camera.h"
#include "PointLight.h"

#include "Objects/Entity.h"
#include "../client/Player.h"
#include "../client/ClientGame.h"

#include "../server/engine/ObjectId.h"
#include <algorithm>
#include <vector>
#include <map>

Scene::Scene() : camera(std::unique_ptr<Camera>(nullptr)), pLight(std::unique_ptr<PointLight>(nullptr)),
    player(nullptr), players(std::vector<std::shared_ptr<Player>>())
{
}
const int Scene::WIDTH = 100;
const int Scene::HEIGHT = 100;

void Scene::Setup()
{
    entities.clear();

    //instanceShader = std::make_shared<Shader>("src/Graphics/Shaders/instancing.vert", "src/Graphics/Shaders/instancing.frag");
    //basicShader = std::make_shared<Shader>("src/Graphics/Shaders/basic_shader.vert", "src/Graphics/Shaders/basic_shader.frag");
    //diffuseShader = std::make_shared<Shader>("src/Graphics/Shaders/basic_shader.vert", "src/Graphics/Shaders/diffuse.frag");
    //modelShader = std::make_shared<Shader>("src/Graphics/Shaders/model_loading.vert", "src/Graphics/Shaders/model_loading.frag");
    //cubeMapShader = std::make_shared<Shader>("src/Graphics/Shaders/cubemap.vert", "src/Graphics/Shaders/cubemap.frag");

    camera = std::unique_ptr<Camera>(new Camera(glm::vec3(0.0f, 9.0f, -15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, -25.0f));
    pLight = std::unique_ptr<PointLight>(new PointLight(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

	// Barn
	std::unique_ptr<StaticObject> barn = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/barn2.obj"));
	barn->Scale(17.0f);
	barn->Translate(glm::vec3(0.0f, 0.0f, 20.0f));

	// Tractors
	std::unique_ptr<StaticObject> red_tractor = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/tractors/red_tractor.obj"));
	red_tractor->Scale(12.0f);
	red_tractor->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	red_tractor->Translate(glm::vec3(17.0f, 0.0f, -13.0f));

	std::unique_ptr<StaticObject> green_tractor = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/tractors/green_tractor.obj"));
	green_tractor->Scale(12.0f);
	green_tractor->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	green_tractor->Translate(glm::vec3(34.0f, 0.0f, 13.0f));

	std::unique_ptr<StaticObject> orange_tractor = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/tractors/orange_tractor.obj"));
	orange_tractor->Scale(12.0f);
	orange_tractor->Rotate(90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	orange_tractor->Translate(glm::vec3(-17.0f, 0.0f, -13.0f));

	// Silo
	std::unique_ptr<StaticObject> silo = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/silo.obj"));
	silo->Scale(10.0f);
	silo->Translate(glm::vec3(-28.0f, 0.0f, -4.0f));

	// Bench
	std::unique_ptr<StaticObject> bench = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/bench3.obj"));
	bench->Scale(4.0f);
	bench->Translate(glm::vec3(40.0f, 3.2f, 0.0f));
	bench->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Pumpkin
	//std::unique_ptr<StaticObject> pumpkinObj = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/pumpkin.obj"));

	// Rocks
	std::unique_ptr<StaticObject> rocks = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/nature/rocks.obj"));
	rocks->Scale(4.0f);
	rocks->Translate(glm::vec3(28.0f, 0.2f, -20.0f));

	// Rocks
	std::unique_ptr<StaticObject> stump = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/nature/stump.obj"));
	stump->Scale(4.0f);
	stump->Translate(glm::vec3(-28.0f, 0.2f, -20.0f));

	// Ground
	std::unique_ptr<StaticObject> ground = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/nature/ground.obj"));
	ground->Scale(15.0f);
	ground->Translate(glm::vec3(0.0f, 100.4f, 0.0f));

	// Seed
	std::unique_ptr<StaticObject> seed = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/pumpkinseed.obj"));
	seed->Scale(0.5f);
	seed->Translate(glm::vec3(0.0f, 1.0f, 0.0f));

	// Tree
	std::unique_ptr<StaticObject> tree = std::unique_ptr<StaticObject>(new StaticObject("assets/map/objects/nature/tree.obj"));
	tree->Scale(10.0f);
	tree->Translate(glm::vec3(-40.0f, 0.2f, -20.0f));

	grass = std::unique_ptr<Grass>(new Grass);
	pumpkin = std::unique_ptr<InstanceObject>(new InstanceObject("assets/map/objects/pumpkin.obj", 10000));

    cubeMap = std::unique_ptr<CubeMap>(new CubeMap);
    cubeMap->LoadCubeMap();

    grass->GetShader() = ShaderManager::Instance()->GetShader("Instancing");
	pumpkin->GetShader() = ShaderManager::Instance()->GetShader("Instancing");
    cubeMap->GetShader() = ShaderManager::Instance()->GetShader("CubeMap");

	//static_objects.push_back(std::move(boat));
	static_objects.push_back(std::move(barn));
	static_objects.push_back(std::move(red_tractor));
	static_objects.push_back(std::move(green_tractor));
	static_objects.push_back(std::move(orange_tractor));
	static_objects.push_back(std::move(silo));
	static_objects.push_back(std::move(rocks));
	static_objects.push_back(std::move(bench));
	static_objects.push_back(std::move(tree));
	//static_objects.push_back(std::move(pumpkinObj));
	static_objects.push_back(std::move(seed));
	static_objects.push_back(std::move(ground));
	
}

void Scene::AddPlayer(int client_id)
{
    //TODO - add client_id field to player
    std::shared_ptr<Player> new_player = std::shared_ptr<Player>(new Player(client_id));

    std::shared_ptr<Shader> modelShader = std::make_shared<Shader>("src/Graphics/Shaders/model_loading.vert", "src/Graphics/Shaders/model_loading.frag");
    new_player->GetShader() = ShaderManager::Instance()->GetShader("Model");

	// maybe we should add players to entities as well
	players.push_back(new_player);

	if (client_id == ClientGame::GetClientId()) {
		printf("set main player to %d\n", client_id);
//		player = new_player; // set your player
	}
}

void Scene::Update()
{
	cubeMap->Update();
	//ground->Update();
	for (auto& const entity : entities)
		entity.second->Update();
}

void Scene::Draw()
{
	cubeMap->Draw();
	grass->Draw();
	pumpkin->Draw();

	for (auto& const obj : static_objects)
		obj->Draw();

	//ground->Draw();
	for (auto& const entity : entities)
	{
		entity.second->Draw();
		//printf("entity ids are %d, %d\n", entity.second->GetClassId(), entity.second->GetObjId());
		if (entity.second->GetClassId() == 0 && entity.second->GetObjId() == 1)
		{
			//printf("Vector for player being drawn is: %f, %f, %f\n", entity.second->Position().x, entity.second->Position().y,
				//entity.second->Position().z);

		}
	}

    // Redrawing players??

}


glm::mat4 Scene::GetViewMatrix()
{
    if (player) return player->GetViewMatrix();
    return camera->GetViewMatrix();
}

glm::vec3 Scene::GetCameraPosition()
{
    if (player) return player->CameraPosition();
    return camera->Position();
}

glm::mat4 Scene::GetPerspectiveMatrix()
{
    if (player) return player->GetPerspectiveMatrix();
    return camera->GetPerspectiveMatrix();
}

void Scene::AddEntity(int cid, int oid, std::unique_ptr<Entity> ent)
{
	std::pair<int, int> p = std::pair<int, int>(cid, oid);
	//entities.insert(std::make_pair(p, std::move(ent)));
	entities[p] = std::move(ent);
}

void Scene::AddEntity(int cid, int oid, float x, float y, float z, float rotw, float rotx, float roty, float rotz)
{
	std::unique_ptr<Player> player;
	std::unique_ptr<Egg> egg;

	switch (cid) {
	case ClassId::PLAYER:
		player = std::unique_ptr<Player>(new Player(x,y,z,rotw,rotx,roty,rotz));
		player->SetModelFile("assets/chickens/objects/pinocchio_chicken.obj");
        player->Spawn(x, y, z);
		player->GetShader() = ShaderManager::Instance()->GetShader("Model");
		player->SetObjId(oid);
		player->SetClassId(cid);
		//player->RotateTo(rotw, rotx, roty, rotz);
		// set main player if the oid matches
		if (oid == ClientGame::instance()->GetClientId())
			Scene::player = player.get();
		//players.push_back(player);

		AddEntity(cid, oid, std::move(player));
		break;
	case ClassId::FLAG:
		egg = std::unique_ptr<Egg>(new Egg(x,y,z));
		egg->SetColor(glm::vec3(0.27f, 0.16f, 0.0f));
        egg->GetShader() = ShaderManager::Instance()->GetShader("Model");
		egg->SetClassId(cid);
		egg->SetObjId(oid);
		AddEntity(cid, oid, std::move(egg));
		break;
	default:
		break;
	}
	
}

void Scene::RemoveEntity(int cid, int oid)
{
	int removed = entities.erase(std::make_pair(cid, oid));
}

std::unique_ptr<Entity>& Scene::GetEntity(int cid, int oid)
{
	std::pair<int, int> p = std::pair<int, int>(cid, oid);
	return entities.find(p)->second;
}
