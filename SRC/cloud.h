#ifndef CLOUD_H
#define CLOUD_H

#include "Engine/resources.h"

class Cloud: public GameObject
{
public:
    Cloud();
    ~Cloud();

public:
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    int id_sprite; //id спрайта для отрисовки
    int speed; //Скорость текущего облака

};

#endif // CLOUD_H
