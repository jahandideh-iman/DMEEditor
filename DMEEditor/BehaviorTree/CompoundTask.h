#ifndef COMPOUNDTASK_H
#define COMPOUNDTASK_H

#include "BehaviorTask.h"

enum CompoundTaskType { t_None, t_SelectorTask, t_SequenceTask};

class CompoundTask : public BehaviorTask
{
public:
    static CompoundTaskType StringToTaskType(QString str);

    CompoundTask(CompoundTaskType type);
    ~CompoundTask();

    QString GetTypeString();

    QVector<BehaviorTask *> GetChildren();

    LinkBox *GetAnEmptyToChildAttachBox() override;

private:
    CompoundTaskType type;
};

#endif // COMPOUNDTASK_H
