#ifndef BEHAVIORTREEEDITOR_H
#define BEHAVIORTREEEDITOR_H

#include "Core/Editor.h"
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
            AddToChildAttachBox(false);
        }

        AttachBox *GetToChildAttachBox() { return toChildAttachBoxes[0];}
        AttachBox *GetAnEmptyToChildAttachBox() override
        {
            if(toChildAttachBoxes[0]->IsAttached())
                return nullptr;
            return toChildAttachBoxes[0];
        }

        void ContributeToMenu(QMenu *menu){menu;}
    };

public:
    BehaviorTreeEditor();
    ~BehaviorTreeEditor();

    void CreateActionTask(QPoint pos);
    void CreateSequenceTask(QPoint pos);
    void CreateSelectorTask(QPoint pos);
    void RemoveTask(BehaviorTask *task);
    void AddTask(BehaviorTask *task, QPoint pos);

    void AttachBoxSelected(AttachBox* attachBox);
    void CancelAttachment();

    void AttachTasks(AttachBox *start, AttachBox *end);
    void AttachTasks(BehaviorTask *parent, BehaviorTask* child);
    void Detach(Attachment* attachment);

    BehaviorTask *GetRoot();
    void SetRoot(BehaviorTask *root);

private:
    void SetInAttachingState(bool flag);



private:
    RootTask *dummyRoot = nullptr;

    AttachBox* lastAttachBox = nullptr;

    QVector<BehaviorTask*> tasks;
};

#endif // BEHAVIORTREEEDITOR_H
