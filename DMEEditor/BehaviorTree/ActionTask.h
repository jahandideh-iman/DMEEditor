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

    LinkBox *GetAnEmptyToChildAttachBox() override;

public slots:
    void SetActionName(const QString &name);

protected:
    void InitialPropertyWidgets() override;

};

#endif // ACTIONTASK_H
