#pragma once

#ifndef BULLET_PHYSICS
#define BULLET_PHYSICS
#include <BulletPhysics\btBulletDynamicsCommon.h>
#include <BulletPhysics\btBulletCollisionCommon.h>
#endif


class Entity
{

protected:

	btDiscreteDynamicsWorld* curWorld;
	btRigidBody* entityRigidBody;
	int objectId;
	int classId;
	int toDelete;

public:

	Entity(int classid, int objectid, btDiscreteDynamicsWorld* physicsworld);

	virtual ~Entity();

	btVector3 GetEntityPosition();

	void Move(btVector3* changeVelocity);

	// Return current rotation quaternion of Player
	btQuaternion GetEntityRotation();

	void SetEntityRotation(float x, float y, float z, float w);

	// Returns object id
	int GetObjectId();

	int GetClassId();

	btDiscreteDynamicsWorld* GetPhysicsWorld() { return curWorld; }

	btRigidBody* GetRigidBody();

	// Marks this entity to be ignored
	void SetToMarked();

	void ResetMark();

	// Checks if this entity is set to be deleted, sets collision detection to ignore
	int MarkStatus();

};