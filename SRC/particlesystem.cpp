#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
    qDebug()<<"Destroy ~ParticleSystem";
}

void ParticleSystem::Init(QHash<QString, QString> property)
{
    count_max = property.value("count_max").toInt();
    count_min = property.value("count_min").toInt();
    speed_max = property.value("speed_max").toInt();
    speed_min = property.value("speed_min").toInt();
    distance_max = property.value("distance_max").toInt();
    distance_min = property.value("distance_min").toInt();
    scal_max = property.value("scal_max").toInt();
    scal_min = property.value("scal_min").toInt();
    count_max_circle = property.value("count_max_circle").toInt();
    count_min_circle = property.value("count_min_circle").toInt();
}

void ParticleSystem::CreateParticles(int id_sprite)
{
    int count_circle = qrand()%(count_max_circle-count_min_circle)+count_min_circle;

    for (int j=0; j<count_circle; j++)
    {
        int count = qrand()%(count_max-count_min)+count_min;

        int color_r = qrand()%255;
        int color_g = qrand()%255;
        int color_b = qrand()%255;

        float angle = 360.0/count;
        for(int i=0; i<count; i++)
        {
            int speed = qrand()%(speed_max-speed_min)+speed_min;
            int distance = qrand()%(distance_max-distance_min)+distance_min;
            int scal = qrand()%(scal_max-scal_min)+scal_min;

            //Свойства для частицы
            QHash<QString, QString> property;
            property.insert("id_sprite", QString::number(id_sprite));
            property.insert("speed", QString::number(speed));
            property.insert("distance", QString::number(distance));
            property.insert("angle", QString::number(i * angle));
            property.insert("color_r", QString::number(color_r));
            property.insert("color_g", QString::number(color_g));
            property.insert("color_b", QString::number(color_b));

            GameObject* particle = new Particle;
            particle->SetName("Particle");
            particle->SetScal(QVector3D(scal, scal, 1));
            particle->SetPos(this->GetPos());
            particle->SetPivot(QVector3D(0.5, 0.5, 0.0));
            particle->SetRotZ(i * -angle);
            particle->Init(property);
            Resources::GAMESCENE()->GetValue("main_scene")->AddGameObject(particle);
        }
    }
}

void ParticleSystem::Update(float dt)
{

}

void ParticleSystem::Draw()
{

}


