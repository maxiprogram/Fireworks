#include "creatorobject.h"

CreatorObject::CreatorObject()
{
}

GameObject* CreatorObject::CreateGameObject(uint type)
{
    type = (Type_GameObject)type;
    switch (type)
    {
        case BackGroundObject:
        {
            return new BackGround();
            break;
        }
        case CloudSystemObject:
        {
            return new CloudSystem();
            break;
        }
        case ParticleSystemObject:
        {
            return new ParticleSystem();
            break;
        }
        default:{return 0;break;}
    }
}
