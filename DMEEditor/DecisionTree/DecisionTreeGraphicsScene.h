#ifndef DECISIONTREEGRAPHICSSCENE_H
#define DECISIONTREEGRAPHICSSCENE_H

#include "Core/EditorGraphicsScene.h"

class DecisionTreeEditor;

class DecisionTreeGraphicsScene : public EditorGraphicsScene
{
    Q_OBJECT
public:
    DecisionTreeGraphicsScene(DecisionTreeEditor *editor);
    ~DecisionTreeGraphicsScene();

protected:
    void ContributeToMenu(QMenu *menu) override;

public slots:
    void CreateActionNodeHelper();
    void CreateDicisionNodeHelper();

private:
    DecisionTreeEditor *GetEditor();
};

#endif // DECISIONTREEGRAPHICSSCENE_H
