#ifndef DECISIONTREESCENE_H
#define DECISIONTREESCENE_H

#include <QGraphicsScene>
#include "UnkownDecisionTreeNode.h"
#include "Node.h"

class DecisionTreeScene : public QGraphicsScene
{
public:
    DecisionTreeScene();
    ~DecisionTreeScene();

    Node* node;


};

#endif // DECISIONTREESCENE_H
