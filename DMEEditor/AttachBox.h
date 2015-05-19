#ifndef ATTACHBOX_H
#define ATTACHBOX_H

#include <QGraphicsRectItem>
#include "MenuContributer.h"

class Attachment;
class BehaviorTask;

class AttachBox : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT
public:
    enum Role{Role_ToParent, Role_ToChild};
public:
    AttachBox(Role role, BehaviorTask *owner = 0);
    ~AttachBox();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

    void ContributeToMenu(QMenu *menu);

    Role GetRole();

    void SetAttachment(Attachment *attachment);
    void SetRemoveable(bool isRemoveable);

    BehaviorTask *GetChildTask();
    BehaviorTask *GetParentTask();
    bool IsAttached();

public slots:
    void AttachBoxSelected();
    void DettachAttachment();

    void Remove();

private:


private:
    Role role;
    QGraphicsRectItem rect;

    Attachment* attachment = nullptr;

    BehaviorTask *ownerTask;

    bool isRemoveable = false;
};

#endif // ATTACHBOX_H
