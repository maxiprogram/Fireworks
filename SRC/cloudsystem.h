#ifndef CLOUDSYSTEM_H
#define CLOUDSYSTEM_H

#include "Engine/resources.h"

#include "cloud.h"


class CloudSystem: public GameObject
{
public:
    CloudSystem();
    ~CloudSystem();

public:
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    int id_sprite; //id спрайта для отрисовки
    int count_cloud; //Количество облаков
    int speed_max; //Максимальная скорость облака
    int speed_min; //Минимальная скорость облака

};

#endif // CLOUDSYSTEM_H
