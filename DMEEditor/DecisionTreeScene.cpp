#include "DecisionTreeScene.h"

DecisionTreeScene::DecisionTreeScene()
{
    node = new UnkownDecisionTreeNode();
    this->addItem(node);
}

DecisionTreeScene::~DecisionTreeScene()
{

}

