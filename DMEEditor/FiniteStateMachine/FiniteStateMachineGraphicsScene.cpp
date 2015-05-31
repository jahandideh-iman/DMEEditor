#include "FiniteStateMachineGraphicsScene.h"
#include <FiniteStateMachine/FiniteStateMachineEditor.h>

FiniteStateMachineGraphicsScene::FiniteStateMachineGraphicsScene(FiniteStateMachineEditor *editor)
    : EditorGraphicsScene(editor)
{
}

FiniteStateMachineGraphicsScene::~FiniteStateMachineGraphicsScene()
{

}

void FiniteStateMachineGraphicsScene::ContributeToMenu(QMenu *menu)
{
   menu->addAction("Create State",this,SLOT(CreateNodeHelper()));
}

void FiniteStateMachineGraphicsScene::CreateNodeHelper()
{
    GetEditor()->CreateState(clickPosition);
}

FiniteStateMachineEditor *FiniteStateMachineGraphicsScene::GetEditor()
{
    return dynamic_cast<FiniteStateMachineEditor *> (editor);
}
