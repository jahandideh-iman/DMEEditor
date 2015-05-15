#ifndef COMPOUNDTASK_H
#define COMPOUNDTASK_H

#include "BehaviorTask.h"

class CompoundTask : public BehaviorTask
{
    Q_OBJECT
public:
    CompoundTask();
    ~CompoundTask();

    void ContributeToMenu(QMenu* menu);

public slots:
    void AddRemoveableChildAttachBox();
};

#endif // COMPOUNDTASK_H
