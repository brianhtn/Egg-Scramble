#include "engine.h"
#include "EntitySpawner.h"
#include <vector>
#include <time.h>

Engine::Engine()
{
    world = new World();
}

Engine::~Engine()
{
}

void Engine::InitWorld(int num_players)
{
    printf("INITIALIZING WORLD ON SERVER\n");

    // we only need to seed once
    srand(time(NULL));
    // pos_list player_poss = GenerateCoords(num_players);
    // pos_list flag_poss = GenerateCoords(num_players * 2);

    world->Init();
}

void Engine::SpawnRandomPlayer(int player, int team, int skin)
{
    PosInfo p;
    p.id = player;
    p.team_id = team;
    p.skin = skin;
    std::pair<int, int> loc = EntitySpawner::GetRandomLoc();
    p.x = loc.first;
    p.z = loc.second;
    p.y = 3;
    EntitySpawner::Instance()->SpawnPlayer(team, p, world->GetPhysicsWorld());
}

void Engine::SpawnRandomFlag()
{
    PosInfo p;
    std::pair<int, int> loc = EntitySpawner::GetRandomLoc();
    p.x = loc.first;
    p.z = loc.second;
    p.y = 3;
    EntitySpawner::Instance()->SpawnFlag(p, world->GetPhysicsWorld());
}

int Engine::RandomNum(int mod)
{
    return rand() % mod;
}

void Engine::SendPreSpawn(int n)
{
    // Always Spawn the players before other dynamic objects
    world->PreSpawn();

    initialSpawned = true;
}