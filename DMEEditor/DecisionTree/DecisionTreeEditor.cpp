#include "DecisionTreeEditor.h"
#include "DecisionNode.h"
#include "ActionNode.h"
#include "DecisionTreeGraphicsScene.h"


DecisionTreeEditor::DecisionTreeEditor()
{
    scene = new DecisionTreeGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setSceneRect(0,0,1000,1000);
    view->setMouseTracking(true);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setDragMode(QGraphicsView::RubberBandDrag);

    InitialDummyRoot();
}

DecisionTreeEditor::~DecisionTreeEditor()
{
    for(auto node : nodes)
        delete node;
}

void DecisionTreeEditor::CreateActionNode(QPointF position)
{
    AddNode(new ActionNode(), position);
}

void DecisionTreeEditor::CreateDecisionNode(QPointF position)
{
    AddNode(new DecisionNode(), position);
}

void DecisionTreeEditor::SetRoot(DecisionTreeNode *node)
{
    LinkNodes(dummyRoot->GetToChildLinkBox(), node->GetToParentLinkBox());
}

DecisionTreeNode *DecisionTreeEditor::GetRoot()
{
    return dummyRoot->GetChild();
}

void DecisionTreeEditor::OnLinkBoxSelected(LinkBox *selected)
{
    if(lastSelectedLinkBox != nullptr && lastSelectedLinkBox != selected)
    {
        LinkNodes(lastSelectedLinkBox, selected);
        SetLinkingState(false);
    }
    else
    {
        lastSelectedLinkBox = selected;
        SetLinkingState(true);
    }
}

void DecisionTreeEditor::CancelLinking()
{
    SetLinkingState(false);
}

void DecisionTreeEditor::LinkNodes(LinkBox *box1, LinkBox *box2)
{
    Link *link;

    if(box1->IsParent() && box2->IsChild())
        link = new Link(box1, box2);
    else if(box2->IsParent() && box1->IsChild())
        link = new Link(box2, box1);
    else
        return;

    scene->addItem(link);
}

void DecisionTreeEditor::LinkDecisionNodeTrueChild(DecisionNode *parent, DecisionTreeNode *child)
{
    LinkNodes(parent->GetRightChildBox(), child->GetToParentLinkBox());
}

void DecisionTreeEditor::LinkDecisionNodeFalseChild(DecisionNode *parent, DecisionTreeNode *child)
{
    LinkNodes(parent->GetLeftChildBox(), child->GetToParentLinkBox());
}

void DecisionTreeEditor::SetLinkingState(bool state)
{
    if(state == false)
    {
        lastSelectedLinkBox = nullptr;
        ((DecisionTreeGraphicsScene*) scene)->StopMouseTracking();
    }
    else
        ((DecisionTreeGraphicsScene*) scene)->StartMouseTracking(lastSelectedLinkBox);
}

void DecisionTreeEditor::InitialDummyRoot()
{
    dummyRoot = new DummyRootNode();
    AddNode(dummyRoot, QPointF(view->sceneRect().width()/2, 50));
}

void DecisionTreeEditor::AddNode(DecisionTreeNode *node, QPointF pos)
{
    scene->addItem(node);
    nodes.push_back(node);
    node->setPos(pos);
}
