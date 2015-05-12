#ifndef BEHAVIORTREEEDITOR_H
#define BEHAVIORTREEEDITOR_H

#include "Editor.h"
#include "BehaviorTask.h"

class AttachBox;

class BehaviorTreeEditor : public Editor
{
    class RootTask : public BehaviorTask
    {
    public:
        RootTask()
        {
            rect->setBrush(QBrush(Qt::yellow));
            childAttachBox = new AttachBox(AttachBox::Role_Child,this);
            childAttachBox->setY(30);
        }
    };

public:
    BehaviorTreeEditor();
    ~BehaviorTreeEditor();

    void CreateActionTask(QPoint pos);
    void AttachTasks(AttachBox *box1, AttachBox *box2);

private:
    RootTask *root = nullptr;
};

#endif // BEHAVIORTREEEDITOR_H
