#ifndef BEHAVIORTREEEDITOR_H
#define BEHAVIORTREEEDITOR_H

#include "Core/Editor.h"
#include "BehaviorTask.h"

class BehaviorTreeEditor : public Editor
{
    class DummyRoot : public BehaviorTask
    {
    public:
        DummyRoot()
        {
            AddAUnremoveableToChildLinkBox();

            QPolygonF polygon;
            polygon << QPointF(0, 30) << QPointF(30, -30) << QPointF(-30, -30);
            QGraphicsPolygonItem *triangle = new QGraphicsPolygonItem(polygon);
            triangle->setBrush(QBrush(Qt::yellow));
            SetShape(triangle);
            SetLinkBoxesLock(true);
        }

        BehaviorTask *GetChild()
        {
            return  dynamic_cast<BehaviorTask *> (GetToChildLinkBox(0)->GetChildNode());
        }

        LinkBox *GetAnEmptyToChildAttachBox() override
        {
            if(GetToChildLinkBox(0)->IsLinked())
                return nullptr;
            return GetToChildLinkBox(0);
        }

        void ContributeToMenu(QMenu *menu){menu;}
    };

public:
    BehaviorTreeEditor();
    ~BehaviorTreeEditor();

    void CreateActionTask(QPointF pos);
    void CreateSequenceTask(QPointF pos);
    void CreateSelectorTask(QPointF pos);
    void RemoveTask(BehaviorTask *task);
    void AddTask(BehaviorTask *task, QPointF pos);

    void OnLinkBoxSelected(LinkBox *selectedBox);
    void CancelMouseTacking() override;

    void LinkTasks(LinkBox *start, LinkBox *end);
    void LinkTasks(BehaviorTask *parent, BehaviorTask* child);

    BehaviorTask *GetRoot();
    void SetRoot(BehaviorTask *root);

private:
    void SetInLinkingState(bool flag);

    void InitialDummyRoot();

private:
    DummyRoot *dummyRoot = nullptr;

    LinkBox *lastSelectedLinkBox = nullptr;

    QVector<BehaviorTask*> tasks;
};

#endif // BEHAVIORTREEEDITOR_H
