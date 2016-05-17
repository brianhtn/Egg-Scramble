#pragma once

// NOTE:  Only use by  EntitySpawner::instance()->"...methodcall..."

#include "Bullet.h"
#include "Player.h"
#include "Flag.h"
#include "Collectable.h"
#include <map>


class EntitySpawner
{
private:
	std::map<std::pair<int, unsigned int>, Entity* > entities;
	static EntitySpawner *spawnInstance;
	EntitySpawner();
	unsigned int oid0;  // player
	unsigned int oid1;  // flag
	unsigned int oid2;  // bullet

public:

	~EntitySpawner();

	static EntitySpawner *instance();

	Player* spawnPlayer(int teamid, PosInfo pos, btDiscreteDynamicsWorld* physicsWorld);

	Flag*  spawnFlag(PosInfo pos, btDiscreteDynamicsWorld* physicsWorld);

	Bullet* spawnBullet(int playerid, int teamid, int damage, const btVector3* pos, btVector3* velocity, btDiscreteDynamicsWorld* physicsWorld);

	void AddEntity(int cid, unsigned int oid, Entity* ent);

};