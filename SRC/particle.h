#ifndef PARTICLE_H
#define PARTICLE_H

#include "Engine/resources.h"

class Particle: public GameObject
{
public:
    Particle();
    ~Particle();

    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    int status; //статус: 1 - уже достигла заданного расстояния; 0 - не достигла заданного расстояния
    int id_sprite; //id спрайта для отрисовки
    int speed; //Скорость движения
    float distance; //Расстояние
    int gravity; //Гравитация
    float alpha; //Альфа для исчезновения
    QVector3D direction; //Направление движения
    QVector3D start_pos; //Стартовая позиция частицы
    QVector4D color; //Цвет частицы
};

#endif // PARTICLE_H
