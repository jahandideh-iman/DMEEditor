#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>

class StateNode;

class StateTransition : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    StateTransition(StateNode* startState, StateNode* endState, QString condition = "");
    ~StateTransition();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    StateNode *GetStartNode();
    StateNode *GetEndNode();

    void RemoveFromStates();
    QString GetConditionName();

public slots:

    void SetConditionName(const QString& value);

private:
    void InitialPropertyWidgets();

private:
    StateNode* startNode = nullptr;
    StateNode* endNode = nullptr;

    //QGraphicsLineItem* line = nullptr;
    QGraphicsPathItem* path = nullptr;
    QPainterPath* pathPainter = nullptr;
    QGraphicsRectItem *rect = nullptr;
    QGraphicsTextItem * conditionNameTextItem = nullptr;


    QString conditionName;


};

#endif // ARROW_H
