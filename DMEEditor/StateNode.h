#ifndef STATENODE_H
#define STATENODE_H

#include <QGraphicsItem>
#include <QVector>
#include <vector>
#include <QGraphicsTextItem>

using std::vector;

class StateLink;

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

    void AddOutLink(StateLink* link);
    void AddInLink(StateLink* link);
    void RemoveOutLink(StateLink* link);
    void RemoveInLink(StateLink* link);

    QVector<StateLink*> & GetOutLinks();
    QVector<StateLink*> & GetInLinks();

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

       QVector<StateLink*> outLinkes;
       QVector<StateLink*> inLinkes;

       QString stateName;
       QString updateActionName;
       QString entryActionName;
       QString exitActionName;

       bool isRoot = false;

       QGraphicsTextItem *stateNameTextItem = nullptr;
};

#endif // STATENODE_H
