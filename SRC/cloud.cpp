#include "cloud.h"

Cloud::Cloud()
{

}

Cloud::~Cloud()
{
    qDebug()<<"Destroy ~Cloud";
}


void Cloud::Init(QHash<QString, QString> property)
{
    id_sprite = property.value("id_sprite").toInt();
    speed = property.value("speed").toInt();
    this->SetName("cloud");
}

void Cloud::Update(float dt)
{
    this->MoveX(speed*dt);
    if (this->GetPosX()>Setting::GetViewPort().width()+200)
    {
        this->SetPosX(-200);
    }

}

void Cloud::Draw()
{
    glDepthMask(false);
    ///*Вывод Облака
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetWidth(),
                                                            Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetHeight());
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Облака*/
    glDepthMask(true);
}
