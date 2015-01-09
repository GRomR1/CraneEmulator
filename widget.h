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
#include "LeftCrutchItem.h"
#include "RightCrutchItem.h"
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
    void addText(QString txt);
    void sceneClicked(QPointF point);

private slots:
    void on__pushButtonDerrickRotatePlus_clicked();
    void on__pushButtonDerrickRotateMinus_clicked();
    void on__pushButtonOutriggerRotatePlus_clicked();
    void on__pushButtonOutriggerRotateMinus_clicked();
    void on__pushButtonRopeHookPlus_clicked();
    void on__pushButtonTelescopicPlus_clicked();
    void on__pushButtonTelescopicMinus_clicked();
    void on__pushButtonRopeHookMinus_clicked();
    void on__pushButtonLeftCrutchPlus_clicked();
    void on__pushButtonLeftCrutchMinus_clicked();
    void on__pushButtonRightCrutchPlus_clicked();
    void on__pushButtonRightCrutchMinus_clicked();
    void on__verticalSliderScale_valueChanged(int value);
    void on__verticalSliderLeftCrutch_sliderReleased();
    void on__verticalSliderRightCrutch_sliderReleased();

    void on__verticalSliderDerrick_sliderReleased();

    void on__verticalSliderOutrigger_sliderReleased();

    void on__verticalSliderTelescopic_sliderReleased();

    void on__pushButtonPillarPlus_clicked();

    void on__pushButtonPillarMinus_clicked();

    void on__verticalSliderPillar_sliderReleased();

    void drawPoint(QPointF p);

private:
    Ui::Widget *ui;
    LeftCrutchItem *_leftCrutch;
    RightCrutchItem *_rightCrutch;
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
};

#endif // WIDGET_H
