#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>

class StateNode;

class StateLink : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    StateLink(StateNode* startState, StateNode* endState, QString condition = "");
    ~StateLink();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    StateNode *GetStartNode();
    StateNode *GetEndNode();

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
