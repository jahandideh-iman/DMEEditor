#include "DecisionTreeGraphicsScene.h"
#include "DecisionTreeEditor.h"
#include "DecisionTreeNode.h"

DecisionTreeGraphicsScene::DecisionTreeGraphicsScene(DecisionTreeEditor *editor) : EditorGraphicsScene(editor)
{

}

DecisionTreeGraphicsScene::~DecisionTreeGraphicsScene()
{

}

void DecisionTreeGraphicsScene::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Create Action Node",this, SLOT(CreateActionNodeHelper()));
    menu->addAction("Create Decision Node", this, SLOT(CreateDicisionNodeHelper()));
}

void DecisionTreeGraphicsScene::CreateActionNodeHelper()
{
    GetEditor()->CreateActionNode(clickPosition);
}

void DecisionTreeGraphicsScene::CreateDicisionNodeHelper()
{
    GetEditor()->CreateDecisionNode(clickPosition);
}

DecisionTreeEditor *DecisionTreeGraphicsScene::GetEditor()
{
    return dynamic_cast<DecisionTreeEditor *> (editor);
}
