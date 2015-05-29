#ifndef BEHAVIORTASK_H
#define BEHAVIORTASK_H

#include <QGraphicsItem>
#include "AttachBox.h"
#include "Utilities/MenuContributer.h"

class BehaviorTask : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT
public:
    BehaviorTask();
    virtual ~BehaviorTask();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void ContributeToMenu(QMenu *menu);

    AttachBox *GetToParentAttachBox();
    virtual AttachBox *GetAnEmptyToChildAttachBox() = 0;

public slots:
    void AddToChildAttachBox(bool isRemoveable = false);
    void RemoveToChildAttachBox(AttachBox *box);
    void Remove();

private:
    void RearrangeToChildAttachBoxes();

protected:
    QGraphicsRectItem *rect = nullptr;

    AttachBox *toParentAttachBox = nullptr;

    QVector<AttachBox *> toChildAttachBoxes;


};

#endif // BEHAVIORTASK_H
