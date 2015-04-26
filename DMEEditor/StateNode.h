#ifndef STATENODE_H
#define STATENODE_H

#include <QGraphicsItem>
#include <QVector>
#include <vector>
#include <QGraphicsTextItem>

using std::vector;

class StateTransition;

class StateNode : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType+16 };
    int type() const { return Type; }
    StateNode(QString name = "", QString updateAction = "", QString entryAction = "", QString exitAction = "");
    ~StateNode();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

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


public slots:
    void SetStateName(const QString& value);
    void SetUpdateActionName(const QString& value);
    void SetEntryActionName(const QString& value);
    void SetExitActionName(const QString& value);

private:
    void InitialPropertyWidgets();

private:
       QGraphicsEllipseItem* ellipse = nullptr;

       QVector<StateTransition*> outLinks;
       QVector<StateTransition*> inLinks;

       QString stateName;
       QString updateActionName;
       QString entryActionName;
       QString exitActionName;

       bool isRoot = false;

       QGraphicsTextItem *stateNameTextItem = nullptr;
};

#endif // STATENODE_H
