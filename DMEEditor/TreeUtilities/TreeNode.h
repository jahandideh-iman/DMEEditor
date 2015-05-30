#ifndef NODE_H
#define NODE_H

#include <QGraphicsObject>
#include "Utilities/MenuContributer.h"
#include "LinkBox.h"

class TreeNode : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT

public:
    TreeNode(QGraphicsItem *parent = nullptr);
    virtual ~TreeNode();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    QRectF boundingRect() const override;

    void ContributeToMenu(QMenu *menu) override;

    void SetShape(QGraphicsItem *newShape);

    virtual void OnLinkBoxSelected(LinkBox *selectedBox) ;
    virtual void OnLinkBoxLinked(LinkBox *box, Link *link);
    virtual void Remove();

    void RemoveToChildLinkBox(LinkBox *box);

    LinkBox *GetToChildLinkBox(int index);
    LinkBox *GetToParentLinkBox();

public slots:
    void AddARemoveableToChildLinkBox();
    void AddAUnremoveableToChildLinkBox();

    void RemoveSlot();

protected:
    void SetLinkBoxesLock(bool lock);

    virtual void RearrangeToChildLinkBoxes();
    virtual void RearrangeToParentLinkBox();

    void InitialToParentLinkBox();

    void SetNodeName(const QString& value);
    QString GetNodeName();

protected:
    LinkBox *toParentLinkBox  = nullptr;
    QVector<LinkBox *> toChildLinkBoxes;

private:
    QGraphicsItem *shape = nullptr;

    bool isLinkBoxesLocked = false;

    QGraphicsTextItem *nodeName = nullptr;
};

#endif // NODE_H
