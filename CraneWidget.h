#ifndef CRANEWIDGET_H
#define CRANEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtSvg/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgWidget>

#include "AbstractItem.h"
#include "view-side\Side_RopeHookItem.h"
#include "view-side\Side_TelescopicItem.h"
#include "view-side\Side_DerrickItem.h"
#include "view-side\Side_HookItem.h"
#include "view-side\Side_OutriggerItem.h"
#include "view-side\Side_PillarItem.h"
#include "view-side\Side_OtherItem.h"
#include "view-side\Side_CrutchItem.h"
#include "view-side\Side_EllipseOutriggerItem.h"
#include "view-side\Side_EllipseHookItem.h"

#include "view-top\Top_TelescopicItem.h"
#include "view-top\Top_DerrickItem.h"
#include "view-top\Top_OutriggerItem.h"
#include "view-top\Top_PillarItem.h"
#include "view-top\Top_OtherItem.h"

namespace Ui {
class CraneWidget;
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
        event->accept();
//        QGraphicsScene::mousePressEvent(event);
    }
};



class CraneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CraneWidget(QWidget *parent = 0);
    ~CraneWidget();

public slots:
    void powerOn(bool b);           ///< Питание (вкл/выкл) (1/0)
    void lightOn(bool b);           ///< Гудок (вкл/выкл) (1/0)
    void soundSignalOn(bool b);     ///< Питание (вкл/выкл) (1/0)
    void pillarUp(int value);       ///< Поворот стойки - по часовой стрелке (1..9)
    void pillarDown(int value);     ///< Поворот стойки - против часовой стрелке (1..9)
    void derrickUp(int value);      ///< Подъемная стрела - подъем (1..9)
    void derrickDown(int value);    ///< Подъемная стрела - опускание (1..9)
    void outriggerUp(int value);    ///< Выносная стрела - подъем (1..9)
    void outriggerDown(int value);  ///< Выносная стрела - опускание (1..9)
    void telescopicUp(int value);   ///< Телескопическая стрела - выдвижение (1..9)
    void telescopicDown(int value); ///< Телескопическая стрела - втягивание (1..9)
    void hookUp(int value);         ///< Лебедка(крюк) - подъем (1..9)
    void hookDown(int value);       ///< Лебедка(крюк) - опускание (1..9)
    void leftCrutchUp(int value);   ///< Левая опора - подъем (1..9)
    void leftCrutchDown(int value); ///< Левая опора - опускание (1..9)
    void rightCrutchUp(int value);  ///< Правая опора - подъем (1..9)
    void rightCrutchDown(int value);///< Правая опора - опускание (1..9)

    void addText(QString txt); //добавляет текст в окно для отладочных сообщение
    void sceneClicked(QPointF point); //добавляет точку в место клика на сцене
    void sceneTopClicked(QPointF point); //добавляет точку в место клика на сцене сверху

signals:
    void signalPowerOn();
    void signalPowerOff();
    void signalLightOn();
    void signalLightOff();
    void temperatureHigh();
    void temperatureNormal();
    void hookIsWarning();
    void hookIsNormal();

private slots:
    void drawPoint(QPointF p); //отображает зеленую точку в заданных координатах
    void showHookWarning(); //показ сообщения о опасности накручивания троса
    void stopHookWarning(); //остановить показ сообщения о опасности накручивания троса
    void showTemperatureWarning(); //показ сообщения о перегрева ОЖ
    void stopTemperatureWarning(); //остановить показ сообщения о перегрева ОЖ
    void on__pushButtonSetTemperatureWarning_clicked(bool checked); //обработчик кнопки для показа сообщения о перегреве ОЖ
    void on__verticalSliderScale_valueChanged(int value); //обработчик слайдера масштаба
    void on__pushButtonDebug_clicked();
    void on__pushButtonPower_clicked(bool checked); //обработчик кнопки для включения крана
    void on__pushButtonLight_clicked(bool checked); //обработчик кнопки для включения подсветки крана

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

private:
    Ui::CraneWidget *ui;
    Side::CrutchItem *_leftCrutch;
    Side::CrutchItem *_rightCrutch;
    Side::PillarItem *_pillar;
    Side::DerrickItem *_derrick;
    Side::OutriggerItem *_outrigger;
    Side::TelescopicItem *_telescopic;
    Side::RopeHookItem *_ropeHook;
    Side::HookItem *_hook;

    Side::OtherItem *_ellipseDerrick;
    Side::EllipseOutriggerItem *_ellipseOutrigger;
    Side::EllipseHookItem *_ellipseHook;
    Side::OtherItem *_ground;

    QGraphicsEllipseItem *_itemEllipse;
    QGraphicsEllipseItem *_itemEllipseForDebug;
    QGraphicsEllipseItem *_itemEllipseTop;
    GraphicsScene *_scene;



    Top::PillarItem *_pillarTop;
    Top::OtherItem *_pillarRectTop;
    Top::DerrickItem *_derrickTop;
    Top::OutriggerItem *_outriggerTop;
    Top::TelescopicItem *_telescopicTop;

    GraphicsScene *_sceneTop;

};

#endif // CRANEWIDGET_H
