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
            AddChildAttachBox();
        }

        void ContributeToMenu(QMenu *menu){}
    };

public:
    BehaviorTreeEditor();
    ~BehaviorTreeEditor();

    void CreateActionTask(QPoint pos);
    void CreateSequenceTask(QPoint pos);
    void CreateSelectorTask(QPoint pos);
    void RemoveTask(BehaviorTask *task);

    void AttachBoxSelected(AttachBox* attachBox);
    void CancelAttachment();

    void AttachTasks(AttachBox *start, AttachBox *end);
    void Detach(Attachment* attachment);

private:
    void SetInAttachingState(bool flag);

    void AddTask(BehaviorTask *task, QPoint pos);

private:
    RootTask *root = nullptr;

    AttachBox* lastAttachBox = nullptr;

    QVector<BehaviorTask*> tasks;
};

#endif // BEHAVIORTREEEDITOR_H
