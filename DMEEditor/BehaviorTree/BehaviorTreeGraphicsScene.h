#ifndef BEHAVIORTREEGRAPHICSSCENE_H
#define BEHAVIORTREEGRAPHICSSCENE_H

#include "Core/EditorGraphicsScene.h"

class BehaviorTreeEditor;

class BehaviorTreeGraphicsScene : public EditorGraphicsScene
{
    Q_OBJECT
public:
    BehaviorTreeGraphicsScene(BehaviorTreeEditor *editor);
    ~BehaviorTreeGraphicsScene();

public slots:
    void CreateActionTaskHelper();
    void CreateSelectorTaskHelper();
    void CreateSequenceTaskHelper();

protected:
    void ContributeToMenu(QMenu *menu);

private:
    BehaviorTreeEditor *GetEditor();

};

#endif // BEHAVIORTREEGRAPHICSSCENE_H
