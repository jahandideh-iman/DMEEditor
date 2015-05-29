#ifndef COMPOUNDTASK_H
#define COMPOUNDTASK_H

#include "BehaviorTask.h"

enum CompoundTaskType { t_None, t_SelectorTask, t_SequenceTask};

class CompoundTask : public BehaviorTask
{
    Q_OBJECT
public:

    static CompoundTaskType StringToTaskType(QString str);

    CompoundTask(CompoundTaskType type);
    ~CompoundTask();

    void ContributeToMenu(QMenu* menu);

    QString GetTypeString();

    QVector<BehaviorTask *> GetChildren();

    AttachBox *GetAnEmptyToChildAttachBox() override;

public slots:
    void AddRemoveableChildAttachBox();

private:
    CompoundTaskType type;
};

#endif // COMPOUNDTASK_H
