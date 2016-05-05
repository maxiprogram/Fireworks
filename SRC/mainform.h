#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QCoreApplication>
#include <QMessageBox>
#include <QTime>
#include <QDebug>

#include "Engine/resources.h"
#include "creatorobject.h"

#include "bullet.h"

class MainForm : public QWindow, public QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainForm(QWindow *parent = 0);
    ~MainForm();

    virtual void render(); //Основная отрисовка
    virtual void initialize(); //Иницилизация сцены

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *key);
    void keyReleaseEvent(QKeyEvent *key);

    void resizeEvent(QResizeEvent * event);

private:
    bool m_update_pending;
    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
    static CreatorObject* CreateObject;
};

#endif // MAINFORM_H
