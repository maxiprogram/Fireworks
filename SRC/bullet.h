#ifndef BULLET_H
#define BULLET_H

#include "Engine/resources.h"
#include "particlesystem.h"

class Bullet: public GameObject
{
public:
    Bullet();
    ~Bullet();

    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    float frame_x; //Для анимации
    int id_sprite_path, id_sprite_boom; //id спрайтов для отрисовки
    QVector4D color; //Цвет снаряда
    float finish_pos_y; //Точка взрыва
    float speed; //Скорость движения
    int status; //статус: 1 - ещё летит; 0 - уже прилетела

};

#endif // BULLET_H
