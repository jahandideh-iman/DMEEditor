#ifndef BEHAVIORTASK_H
#define BEHAVIORTASK_H

#include <QGraphicsItem>
#include "AttachBox.h"
#include "MenuContributer.h"

class BehaviorTask : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT
public:
    BehaviorTask();
    virtual ~BehaviorTask();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void ContributeToMenu(QMenu *menu);

public slots:
    void AddChildAttachBox(bool isRemoveable = false);
    void RemoveChildAttachBox(AttachBox *box);
    void Remove();

private:
    void RearrangeChildAttachBoxes();

protected:
    QGraphicsRectItem *rect = nullptr;

    AttachBox *parrentAttachBox = nullptr;

    QVector<AttachBox *> childAttachBoxes;


};

#endif // BEHAVIORTASK_H
