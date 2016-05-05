#include "particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
    qDebug()<<"Destroy ~Particle";
}

void Particle::Init(QHash<QString, QString> property)
{
    id_sprite = property.value("id_sprite").toInt();
    speed = property.value("speed").toInt();
    distance = property.value("distance").toFloat();
    float angle = property.value("angle").toFloat();

    Transformer tr;
    tr.SetRotZ(angle);
    direction.setX(1);
    direction.setY(0);
    direction = direction * tr.GetMatrix();
    direction.normalize();

    start_pos.setX(this->GetPosX());
    start_pos.setY(this->GetPosY());
    start_pos.setZ(this->GetPosZ());

    int red = property.value("color_r").toInt();
    int green = property.value("color_g").toInt();
    int blue = property.value("color_b").toInt();

    color.setX(red/255.0);
    color.setY(green/255.0);
    color.setZ(blue/255.0);
    color.setW(1.0);

    alpha = 1.0;

    status = 0;
}

void Particle::Update(float dt)
{
    QVector3D current_distance = this->GetPos()-start_pos;

    if (status==0)
    {
        if (current_distance.length()>distance) //Если частица достигла заданного расстояния
        {
            status = 1;
            gravity = qrand()%99-100;

        }else //Если частица не достигла заданного расстояния
        {
            this->MovePos(direction * speed * dt);
        }
    }else //Если частица достигла заданного расстояния
    {
        alpha-=0.009;
        this->MovePos(direction);
        this->MoveY(gravity * dt);
        if (alpha<0)
            Resources::GAMESCENE()->GetValue("main_scene")->DeleteGameObject(this);
    }
}

void Particle::Draw()
{
    glDepthMask(false);
    ///*Вывод Частицы
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetWidth(),
                                                            Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetHeight());
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue("Color", color);
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue("Alpha", alpha);
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Частицы*/
    glDepthMask(true);
}
