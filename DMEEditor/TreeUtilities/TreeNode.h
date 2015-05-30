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

    virtual void OnLinkBoxSelected(LinkBox *selectedBox) = 0;
    virtual void OnLinkBoxLinked(LinkBox *box, Link *link);

    LinkBox *GetToChildLinkBox(int index);
    LinkBox *GetToParentLinkBox();

public slots:
    void AddARemoveableToChildLinkBox();
    void AddAUnremoveableToChildLinkBox();

    void Remove();

protected:
    void SetLinkBoxesLock(bool lock);

    virtual void RearrangeToChildLinkBoxes();
    virtual void RearrangeToParentLinkBox();

    void CreateToParentLinkBox();

    void SetNodeName(const QString& value);

private:
    QGraphicsItem *shape = nullptr;

    LinkBox *toParentLinkBox  = nullptr;
    QVector<LinkBox *> toChildLinkBoxes;

    bool isLinkBoxesLocked = false;

    QGraphicsTextItem *nodeName = nullptr;

};

#endif // NODE_H
