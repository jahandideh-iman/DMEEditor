#ifndef COMPOUNDTASK_H
#define COMPOUNDTASK_H

#include "BehaviorTask.h"

class CompoundTask : public BehaviorTask
{
public:
    CompoundTask();
    ~CompoundTask();

    QVector<BehaviorTask *> GetChildren();

    LinkBox *GetAnEmptyToChildAttachBox() override;

    virtual QString GetType() = 0;

protected:
    void RearrangeToParentLinkBox() override;
    void RearrangeToChildLinkBoxes() override;

};

#endif // COMPOUNDTASK_H
