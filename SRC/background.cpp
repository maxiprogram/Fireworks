#include "background.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
    qDebug()<<"Destroy ~BackGround";
}

void BackGround::Init(QHash<QString, QString> property)
{
    id_sprite = property.value("id_sprite").toInt();
}

void BackGround::Update(float dt)
{
    //Задать позицию фона учитывая позицию текущей камеры
    this->SetPos(QVector3D(Resources::CAMERA()->GetCurrentCamera()->GetPosX(), Resources::CAMERA()->GetCurrentCamera()->GetPosY(), -4));
    //Задать масштаб фона учитывая ширину и высоту окна
    this->SetScal(QVector3D(Setting::GetViewPort().width(), Setting::GetViewPort().height(), 1));
}

void BackGround::Draw()
{
    ///*Вывод Фона
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetWidth(),
                                                            Resources::SPRITE()->GetValue(id_sprite)->GetTexture()->GetHeight());
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Фона*/
}
