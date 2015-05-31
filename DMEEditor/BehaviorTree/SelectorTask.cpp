#include "SelectorTask.h"

SelectorTask::SelectorTask()
{
    SetNodeName("?", 2);
}

SelectorTask::~SelectorTask()
{

}

QString SelectorTask::GetType()
{
    return "SelectorTask";
}
