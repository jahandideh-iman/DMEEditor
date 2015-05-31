#ifndef SELECTORTASK_H
#define SELECTORTASK_H

#include "CompoundTask.h"

class SelectorTask : public CompoundTask
{
public:
    SelectorTask();
    ~SelectorTask();

    QString GetType() override;


};

#endif // SELECTORTASK_H
