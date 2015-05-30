#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include "Core/Editor.h"
#include "DecisionTreeNode.h"

class DecisionNode;

class DecisionTreeEditor : public Editor
{
public:
    DecisionTreeEditor();
    ~DecisionTreeEditor();

    class DummyRootNode : public DecisionTreeNode
    {
    public:
        DummyRootNode()
        {
            AddAUnremoveableToChildLinkBox();

            QPolygonF polygon;
            polygon << QPointF(0, 30) << QPointF(30, -30) << QPointF(-30, -30);
            QGraphicsPolygonItem *triangle = new QGraphicsPolygonItem(polygon);
            triangle->setBrush(QBrush(Qt::yellow));
            SetShape(triangle);
            SetLinkBoxesLock(true);
        }

        DecisionTreeNode *GetChild()
        {
            return  dynamic_cast<DecisionTreeNode *> (GetToChildLinkBox()->GetChildNode());
        }

        LinkBox *GetToChildLinkBox()
        {
            return DecisionTreeNode::GetToChildLinkBox(0);
        }

        void ContributeToMenu(QMenu *menu) override { menu;}

    protected:
        void RearrangeToChildLinkBoxes() override
        {
            GetToChildLinkBox()->setPos(0,30);
        }
    };

    void CreateActionNode(QPointF position);
    void CreateDecisionNode(QPointF position);
    void AddNode(DecisionTreeNode *node, QPointF pos);
    void RemoveNode(DecisionTreeNode *node);

    void SetRoot(DecisionTreeNode *node);
    DecisionTreeNode *GetRoot();

    void OnLinkBoxSelected(LinkBox *selected);
    void CancelMouseTacking() override;

    void LinkNodes(LinkBox *box1, LinkBox *box2);
    void LinkDecisionNodeTrueChild(DecisionNode *parent, DecisionTreeNode *child);
    void LinkDecisionNodeFalseChild(DecisionNode *parent, DecisionTreeNode *child);

private:
    void SetLinkingState(bool state);

    void InitialDummyRoot();

private:
    DummyRootNode *dummyRoot = nullptr;

    LinkBox *lastSelectedLinkBox = nullptr;

    QVector<DecisionTreeNode *> nodes;

};

#endif // DECISIONTREEEDITOR_H
