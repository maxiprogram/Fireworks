#include "bullet.h"

Bullet::Bullet()
{

}


Bullet::~Bullet()
{
    qDebug()<<"Destroy ~Bullet";
}

void Bullet::Init(QHash<QString, QString> property)
{
    id_sprite_path = property.value("id_sprite_path").toInt();
    id_sprite_boom = property.value("id_sprite_boom").toInt();
    finish_pos_y = property.value("finish_pos_y").toFloat();
    speed = property.value("speed").toFloat();
    int red = property.value("color_r").toInt();
    int green = property.value("color_g").toInt();
    int blue = property.value("color_b").toInt();
    color.setX(red/255.0);
    color.setY(green/255.0);
    color.setZ(blue/255.0);
    color.setW(1.0);

    status = 1;

    frame_x = 0;
}

void Bullet::Update(float dt)
{
    if (status==1) //Если снаряд в пути
    {
        if (this->GetPosY()>=finish_pos_y)
        {
            status = 0;
            frame_x = 0;
            ParticleSystem* particle_system = (ParticleSystem*)Resources::GAMEOBJECT()->GetValue("ParticleSystem");
            particle_system->SetPos(this->GetPos());
            particle_system->CreateParticles(4);
            particle_system->CreateParticles(5);
        }else
        {
            this->MoveY(speed*dt);
            frame_x+=0.1;
            if (frame_x>2)
            {
                frame_x = 0;
            }
        }
    }else //Если снаряд достиг конечной точки
    {
        this->SetScal(QVector3D(100, 100, 1));
        this->SetPivot(QVector3D(0.5, 0.5, 1));
        frame_x+=0.2;
        if (frame_x>8)
        {
            Resources::GAMESCENE()->GetValue("main_scene")->DeleteGameObject(this);
        }
    }
}

void Bullet::Draw()
{
    glDepthMask(false);
    if (status==1) //Если снаряд в пути
    {
        ///*Вывод Снаряда
        ManagerSprite::getInstance()->GetValue(id_sprite_path)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame_x));
        ManagerSprite::getInstance()->GetValue(id_sprite_path)->GetShader()->setUniformValue("Color", color/*QVector4D(0.9, 0.0, 0.0, 1.0)*/);
        ManagerSprite::getInstance()->GetValue(id_sprite_path)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite_path)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite_path)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite_path)->UnBind();
        //Вывод Снаряда*/
    }

    if (status==0) //Если снаряд достиг конечной точки
    {
        ///*Вывод Снаряда
        ManagerSprite::getInstance()->GetValue(id_sprite_boom)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame_x));
        ManagerSprite::getInstance()->GetValue(id_sprite_boom)->GetShader()->setUniformValue("Color", color);
        ManagerSprite::getInstance()->GetValue(id_sprite_boom)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite_boom)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite_boom)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite_boom)->UnBind();
        //Вывод Снаряда*/
    }
    glDepthMask(true);
}
