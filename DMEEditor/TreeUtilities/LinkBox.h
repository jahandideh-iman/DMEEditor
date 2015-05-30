#ifndef LINKBOX_H
#define LINKBOX_H

#include <QGraphicsObject>
#include "Utilities/MenuContributer.h"
#include "Link.h"

class TreeNode;

class LinkBox : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT

public:
    enum Role {Role_ToParent, Role_ToChild};

public:
    LinkBox(Role role, TreeNode *owner = nullptr);
    ~LinkBox();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    QRectF boundingRect() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

    void ContributeToMenu(QMenu *menu) override;

    void SetRemoveable(bool isRemoveable);
    bool IsRemoveable();

    void SetLink(Link *link);
    bool IsLinked();

    bool IsChild();
    bool IsParent();

    TreeNode *GetChildNode();
    TreeNode *GetParentNode();

public slots:
    void Select();
    void Unlink();
    void Remove();

private:
    TreeNode *GetOwnerNode();

private:
    Role role;
    TreeNode *ownerNode;

    QGraphicsRectItem rect;

    Link *link = nullptr;

    bool isRemoveable = false;
};

#endif // LINKBOX_H
