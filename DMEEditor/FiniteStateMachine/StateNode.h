#ifndef STATENODE_H
#define STATENODE_H

#include <QGraphicsObject>
#include "Utilities/MenuContributer.h"


class StateTransition;

class StateNode : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT

    class Circle : public QGraphicsEllipseItem
    {
    public:
        Circle(double radius, QGraphicsItem* parent) : QGraphicsEllipseItem(parent)
        {
            setRect(-radius, -radius , radius *2 , radius * 2);
            this->radius = radius;
        }

        double GetRadius(){ return radius;}
    private:
        double radius;
    };

public:

    StateNode(QString name = "State", QString updateAction = "", QString entryAction = "", QString exitAction = "");
    ~StateNode();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

    void AddOutLink(StateTransition* link);
    void AddInLink(StateTransition* link);
    void RemoveOutLink(StateTransition* link);
    void RemoveInLink(StateTransition* link);

    QVector<StateTransition*> & GetOutLinks();
    QVector<StateTransition*> & GetInLinks();

    void SetRootFlag(bool flag);
    bool IsRoot();

    QString GetStateName();
    QString GetUpdateActionName();
    QString GetEntryActionName();
    QString GetExitActionName();

    void ContributeToMenu(QMenu *menu);

    double GetRadius();


public slots:
    void Connect();
    void Remove();
    void SetAsRoot();

    void SetStateName(const QString& value);
    void SetUpdateActionName(const QString& value);
    void SetEntryActionName(const QString& value);
    void SetExitActionName(const QString& value);

private:
    void InitialPropertyWidgets();

    bool EditorIsInConnectingState();

private:
       Circle* circle = nullptr;

       QVector<StateTransition*> outLinks;
       QVector<StateTransition*> inLinks;

       QString stateName;
       QString updateActionName;
       QString entryActionName;
       QString exitActionName;

       bool isRoot = false;

       bool isBeingTracked = false;

       QGraphicsTextItem *stateNameTextItem = nullptr;
};

#endif // STATENODE_H
