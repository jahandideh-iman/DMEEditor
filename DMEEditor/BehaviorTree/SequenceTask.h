#ifndef SEQUENCETASK_H
#define SEQUENCETASK_H

#include "CompoundTask.h"

class SequenceTask : public CompoundTask
{
public:
    SequenceTask();
    ~SequenceTask();

    QString GetType() override;

private:
    QGraphicsItem *arrow;
};

#endif // SEQUENCETASK_H
