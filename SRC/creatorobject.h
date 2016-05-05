#ifndef CREATOROBJECT_H
#define CREATOROBJECT_H

#include "Engine/creatorgameobject.h"

#include "background.h"
#include "cloudsystem.h"
#include "particlesystem.h"

enum Type_GameObject {BackGroundObject=0, CloudSystemObject=1, ParticleSystemObject=2};

class CreatorObject:public CreatorGameObject
{
public:
    CreatorObject();
    GameObject* CreateGameObject(uint type);
};

#endif // CREATOROBJECT_H
