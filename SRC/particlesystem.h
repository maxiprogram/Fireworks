#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Engine/resources.h"
#include "particle.h"

class ParticleSystem: public GameObject
{
public:
    ParticleSystem();
    ~ParticleSystem();

public:
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();
    void CreateParticles(int id_sprite);

private:
    int count_max, count_min; //Макс./Мин. количество частиц
    int speed_max, speed_min; //Макс./Мин. скорость движения частиц
    int distance_max, distance_min; //Макс./Мин. расстояние частиц
    int scal_max, scal_min; //Макс./Мин. масштаб частиц
    int count_max_circle, count_min_circle; //Макс./Мин. количество кругов из частиц
};

#endif // PARTICLESYSTEM_H
