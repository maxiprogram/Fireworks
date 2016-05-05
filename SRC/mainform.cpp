#include "mainform.h"

//Иницилизация статического класса для создания других динамических классов
CreatorObject* MainForm::CreateObject = 0;

MainForm::MainForm(QWindow *parent) :
    QWindow(parent)
{
    m_device = 0;
    m_context = 0;
    m_update_pending = false;
    setSurfaceType(QWindow::OpenGLSurface);

    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
}

MainForm::~MainForm()
{
    delete m_device;
}

//Иницилизация сцены
void MainForm::initialize()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);

    ///*Настройки экрана и перспективы
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.ortho(0, this->width(), 0, this->height(), -10, 10);
    Setting::SetProjection(proj);
    Setting::SetViewPort(QRectF(0, 0, this->width(), this->height()));
    //Настройки экрана и перспективы*/

    //Создание фабрики по созданию классов
    MainForm::CreateObject = new CreatorObject();

    ///*Загрузка основной сцены
    GameScene* main_scene = new GameScene;
    Resources::GAMESCENE()->Add("main_scene", main_scene);
    if (!main_scene->Load("Resources/main_scene.xml", MainForm::CreateObject))
    {
        QMessageBox::warning(0, "Ошибка загрузки сцены", "Не удалось загрузить 'Resources/main_scene.xml'!");
        QCoreApplication::exit(1);
    }
    //Загрузка основной сцены*/


}

//Основная отрисовка
void MainForm::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice();

    //Дополнительная информация
    int fps = Resources::FPS()->GetFps();
    this->setTitle("FPS="+QString::number(fps) +
                       " X="+QString::number(Resources::MOUSE()->GetX()) +
                       " Y="+QString::number(Setting::GetViewPort().height()-Resources::MOUSE()->GetY())
                       );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Обновление логики сцены
    Resources::GAMESCENE()->GetValue("main_scene")->Update(1.0/fps);
    //Прорисовка всей сцены
    Resources::GAMESCENE()->GetValue("main_scene")->Draw();

    int mouse_x = Resources::MOUSE()->GetX();
    int mouse_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();

    //Если нажата левая кнопка мышки
    if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
    {
        //Свойства снаряда
        QHash<QString, QString> property;
        property.insert("id_sprite_path", "3");
        property.insert("id_sprite_boom", "2");
        property.insert("speed", "100");
        property.insert("finish_pos_y", QString::number(mouse_y));
        property.insert("color_r", QString::number(qrand()%255));
        property.insert("color_g", QString::number(qrand()%255));
        property.insert("color_b", QString::number(qrand()%255));

        GameObject* bullet = new Bullet;
        bullet->SetName("bullet");
        bullet->SetPos(QVector3D(mouse_x, 50, 0.1));
        bullet->SetScal(QVector3D(20, 120, 1));
        bullet->SetPivot(QVector3D(0.5, 1.0, 0.0));
        bullet->Init(property);
        Resources::GAMESCENE()->GetValue("main_scene")->AddGameObject(bullet);

        Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
    }

    //Если нажата клавиша ESC
    if (Resources::KEYBOARD()->GetKey(Qt::Key_Escape))
    {
        QEvent event_exit(QEvent::Close);
        QCoreApplication::sendEvent(this, &event_exit);
        return;
    }

    m_device->setSize(size());

}

void MainForm::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool MainForm::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    case QEvent::Close:
        Resources::DestroyResources(); //Очистка всех ресурсов
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void MainForm::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void MainForm::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context)
    {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();
        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize)
    {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    renderLater();
}

//Обновление мышки при движении
void MainForm::mouseMoveEvent(QMouseEvent *event)
{
    Resources::MOUSE()->Update(event, false);
}

//Обновление мышки при нажатии клавиш
void MainForm::mousePressEvent(QMouseEvent *event)
{
    Resources::MOUSE()->Update(event, true);
}

//Обновление мышки при отжатии клавиш
void MainForm::mouseReleaseEvent(QMouseEvent *event)
{
    Resources::MOUSE()->Update(event, false);
}

//Обновление клавиатуры при нажатии клавиш
void MainForm::keyPressEvent(QKeyEvent *key)
{
    Resources::KEYBOARD()->Update(key);
}

//Обновление клавиатуры при отжатии клавиш
void MainForm::keyReleaseEvent(QKeyEvent *key)
{
    Resources::KEYBOARD()->Update(key, false);
}

//При изменение размера окна
void MainForm::resizeEvent(QResizeEvent * event)
{
    ///*Настройки экрана и перспективы
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.ortho(0, this->width(), 0, this->height(), -10, 10);
    Setting::SetProjection(proj);
    Setting::SetViewPort(QRectF(0, 0, this->width(), this->height()));
    //Настройки экрана и перспективы*/
}
