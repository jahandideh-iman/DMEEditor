#include "ActionTask.h"

ActionTask::ActionTask()
{
    parrentAttachBox = new AttachBox(AttachBox::Role_Parent,this);
    parrentAttachBox->setY(-30);
}

ActionTask::~ActionTask()
{

}


