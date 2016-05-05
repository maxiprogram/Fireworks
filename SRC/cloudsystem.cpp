#include "cloudsystem.h"

CloudSystem::CloudSystem()
{

}

CloudSystem::~CloudSystem()
{
    qDebug()<<"Destroy ~CloudSystem";
}

void CloudSystem::Init(QHash<QString, QString> property)
{
    id_sprite = property.value("id_sprite").toInt();
    int count_max = property.value("count_max").toInt();
    int count_min = property.value("count_min").toInt();

    //Случайное количество облаков от count_min до count_max
    count_cloud = qrand()%(count_max-count_min)+count_min;

    speed_max = property.value("speed_max").toInt();
    speed_min = property.value("speed_min").toInt();

    //Создание облаков
    for (int i=0; i<count_cloud; i++)
    {
        QHash<QString, QString> property; //Свойства для облака
        property.insert("id_sprite", QString::number(id_sprite)); //id спрайта для отрисовки

        int speed = qrand()%(speed_max-speed_min)+speed_min; //случайная скорость
        property.insert("speed", QString::number(speed)); //скорость движения облака

        QVector3D pos_cloud; //Случайная позиция облака
        pos_cloud.setX(qrand()%(int)Setting::GetViewPort().width());
        pos_cloud.setY(qrand()%(int)Setting::GetViewPort().height()/2+Setting::GetViewPort().height()/2);
        pos_cloud.setZ(0.01);

        QVector3D scal_cloud(Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetWidth(),
                             Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetHeight(),
                             1);

        GameObject* new_cloud = new Cloud;
        new_cloud->SetPos(pos_cloud); //Задание позиции
        new_cloud->SetScal(scal_cloud); //Задание масштаба

        new_cloud->Init(property);
        Resources::GAMESCENE()->GetValue("main_scene")->AddGameObject(new_cloud);
    }

}

void CloudSystem::Update(float dt)
{

}

void CloudSystem::Draw()
{

}
