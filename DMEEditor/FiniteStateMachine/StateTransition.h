#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsObject>

#include "Utilities/MenuContributer.h"

class StateNode;
class CurvedArrow;

class StateTransition : public QGraphicsObject , public MenuContributer
{
    Q_OBJECT

public:
    StateTransition(StateNode* startState, StateNode* endState, QString condition = "Condition");
    ~StateTransition();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    StateNode *GetStartNode();
    StateNode *GetEndNode();

    void RemoveFromStates();
    QString GetConditionName();

    void ContributeToMenu(QMenu *menu) override;

    QPointF GetHandlePos();
    void SetHandlePos(float x, float y);

public slots:
    void Remove();
    void SetConditionName(const QString& value);

private:
    void InitialPropertyWidgets();

private:
    StateNode* startNode = nullptr;
    StateNode* endNode = nullptr;

    QGraphicsTextItem * conditionNameTextItem = nullptr;

    QString conditionName;

    CurvedArrow *arrow = nullptr;
};

#endif // ARROW_H
