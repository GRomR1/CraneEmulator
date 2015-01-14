#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtSvg/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgWidget>

#include "AbstractItem.h"
#include "RopeHookItem.h"
#include "TelescopicItem.h"
#include "DerrickItem.h"
#include "HookItem.h"
#include "OutriggerItem.h"
#include "PillarItem.h"
#include "OtherItem.h"
//#include "LeftCrutchItem.h"
//#include "RightCrutchItem.h"
#include "CrutchItem.h"
#include "EllipseOutriggerItem.h"
#include "EllipseHookItem.h"

namespace Ui {
class Widget;
}

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphicsScene(QWidget *parent = 0):
        QGraphicsScene(parent)
    {}
    GraphicsScene(const QRectF & sceneRect, QObject * parent = 0) :
        QGraphicsScene(sceneRect, parent)
    {}

signals:
    void clicked(QPointF point);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        emit clicked(event->scenePos());
        QGraphicsScene::mousePressEvent(event);
    }
};



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void addText(QString txt); //добавляет текст в окно для отладочных сообщение
    void sceneClicked(QPointF point); //добавляет точку в место клика на сцене

private slots:
    void drawPoint(QPointF p); //отображает зеленую точку в заданных координатах
    void showHookWarning(); //показ сообщения о опасности накручивания троса
    void stopHookWarning(); //остановить показ сообщения о опасности накручивания троса
    void showTemperatureWarning(); //показ сообщения о перегрева ОЖ
    void stopTemperatureWarning(); //остановить показ сообщения о перегрева ОЖ
    void on__pushButtonSetTemperatureWarning_clicked(bool checked); //обработчик кнопки для показа сообщения о перегреве ОЖ

    //rope hooh - лебедка
    void on__pushButtonRopeHookPlus_clicked();
    void on__pushButtonRopeHookMinus_clicked();
    void on__verticalSliderRopeHook_valueChanged(int value);

    //telescopic - телескопическая стрела
    void on__pushButtonTelescopicPlus_clicked();
    void on__pushButtonTelescopicMinus_clicked();
    void on__verticalSliderTelescopic_valueChanged(int value);

    //outrigger - выносная стрела
    void on__pushButtonOutriggerRotatePlus_clicked();
    void on__pushButtonOutriggerRotateMinus_clicked();
    void on__verticalSliderOutrigger_valueChanged(int value);

    //derrick - подъемная стрела
    void on__pushButtonDerrickRotatePlus_clicked();
    void on__pushButtonDerrickRotateMinus_clicked();
    void on__verticalSliderDerrick_valueChanged(int value);

    //pillar - стойка
    void on__pushButtonPillarPlus_clicked();
    void on__pushButtonPillarMinus_clicked();
    void on__verticalSliderPillar_valueChanged(int value);

    //left crutch - левая опора
    void on__pushButtonLeftCrutchPlus_clicked();
    void on__pushButtonLeftCrutchMinus_clicked();
    void on__verticalSliderLeftCrutch_valueChanged(int value);

    //right crutch - правая опора
    void on__pushButtonRightCrutchPlus_clicked();
    void on__pushButtonRightCrutchMinus_clicked();
    void on__verticalSliderRightCrutch_valueChanged(int value);


    void on__verticalSliderScale_valueChanged(int value); //обработчик слайдера масштаба

private:
    Ui::Widget *ui;
    CrutchItem *_leftCrutch;
    CrutchItem *_rightCrutch;
    PillarItem *_pillar;
    DerrickItem *_derrick;
    OutriggerItem *_outrigger;
    TelescopicItem *_telescopic;
    RopeHookItem *_ropeHook;
    HookItem *_hook;

    OtherItem *_ellipseDerrick;
    EllipseOutriggerItem *_ellipseOutrigger;
    EllipseHookItem *_ellipseHook;
    OtherItem *_ground;

    GraphicsScene *_scene;
    QGraphicsEllipseItem *_itemEllipse;
    QGraphicsEllipseItem *_itemEllipseForDebug;
};

#endif // WIDGET_H
