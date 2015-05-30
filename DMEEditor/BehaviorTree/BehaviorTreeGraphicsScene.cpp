#include "BehaviorTreeGraphicsScene.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "BehaviorTreeEditor.h"
#include "Core/Application.h"
#include "Utilities/MenuContributer.h"

BehaviorTreeGraphicsScene::BehaviorTreeGraphicsScene(BehaviorTreeEditor *editor) : EditorGraphicsScene(editor)
{
}

BehaviorTreeGraphicsScene::~BehaviorTreeGraphicsScene()
{

}


void BehaviorTreeGraphicsScene::CreateActionTaskHelper()
{
    GetEditor()->CreateActionTask(clickPosition);
}

void BehaviorTreeGraphicsScene::CreateSelectorTaskHelper()
{
    GetEditor()->CreateSelectorTask(clickPosition);
}

void BehaviorTreeGraphicsScene::CreateSequenceTaskHelper()
{
    GetEditor()->CreateSequenceTask(clickPosition);
}

void BehaviorTreeGraphicsScene::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Create Action Node",this, SLOT(CreateActionTaskHelper()));
    menu->addAction("Create Sequence Node", this, SLOT(CreateSequenceTaskHelper()));
    menu->addAction("Create Selector Node", this, SLOT(CreateSelectorTaskHelper()));
}

BehaviorTreeEditor *BehaviorTreeGraphicsScene::GetEditor()
{
    return dynamic_cast<BehaviorTreeEditor *> (editor);
}


