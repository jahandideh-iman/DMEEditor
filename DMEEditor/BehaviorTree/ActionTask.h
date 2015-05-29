#ifndef ACTIONTASK_H
#define ACTIONTASK_H

#include "BehaviorTask.h"

class ActionTask : public BehaviorTask
{
    Q_OBJECT
public:
    ActionTask();
    ~ActionTask();

    QString GetActionName();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    AttachBox *GetAnEmptyToChildAttachBox() override;

public slots:
    void SetActionName(const QString &name);

private:
    void InitialProperties();

private:
    QGraphicsTextItem* actionName;

};

#endif // ACTIONTASK_H
