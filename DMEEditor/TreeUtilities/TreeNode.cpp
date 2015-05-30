#include "TreeNode.h"
#include <QDebug>


TreeNode::TreeNode(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    SetShape(new QGraphicsRectItem(QRect(-40,-30,80,60),this));

    nodeName = new QGraphicsTextItem(this);
    nodeName->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

TreeNode::~TreeNode()
{
    delete shape;
    delete toParentLinkBox;

    for( auto box : toChildLinkBoxes )
        delete box;

    delete nodeName;
}

void TreeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter; option; widget;
}

QRectF TreeNode::boundingRect() const
{
    return shape->boundingRect();
}

void TreeNode::SetShape(QGraphicsItem *newShape)
{
    delete shape;
    shape = newShape;
    newShape->setZValue(0);
    newShape->setParentItem(this);
    newShape->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

void TreeNode::OnLinkBoxSelected(LinkBox *selectedBox)
{
    selectedBox;
}

void TreeNode::OnLinkBoxLinked(LinkBox *box, Link *link)
{
    box; link;
}

void TreeNode::ContributeToMenu(QMenu *menu)
{
    if(isLinkBoxesLocked == false)
         menu->addAction("Add Link",this, SLOT(AddARemoveableToChildLinkBox()));

    menu->addAction("Remove",this, SLOT(RemoveSlot()));
}

void TreeNode::SetLinkBoxesLock(bool lock)
{
    isLinkBoxesLocked = lock;
}

void TreeNode::AddARemoveableToChildLinkBox()
{
    if(isLinkBoxesLocked)
        return;

    auto box = new LinkBox(LinkBox::Role_ToChild,this);
    box->setZValue(1);
    box->SetRemoveable(true);
    toChildLinkBoxes.push_back(box);

    RearrangeToChildLinkBoxes();
}

void TreeNode::AddAUnremoveableToChildLinkBox()
{
    if(isLinkBoxesLocked)
        return;

    auto box = new LinkBox(LinkBox::Role_ToChild,this);
    box->setZValue(1);
    box->SetRemoveable(false);
    toChildLinkBoxes.push_back(box);

    RearrangeToChildLinkBoxes();
}

void TreeNode::RemoveSlot()
{
    Remove();
}

void TreeNode::Remove()
{
    delete this;
}

void TreeNode::RemoveToChildLinkBox(LinkBox *box)
{
    toChildLinkBoxes.removeAll(box);
    delete box;
    RearrangeToChildLinkBoxes();
}

LinkBox *TreeNode::GetToChildLinkBox(int index)
{
    if(index >= toChildLinkBoxes.size())
        return nullptr;
    return toChildLinkBoxes[index];
}

LinkBox *TreeNode::GetToParentLinkBox()
{
    return toParentLinkBox;
}

void TreeNode::RearrangeToChildLinkBoxes()
{

}

void TreeNode::RearrangeToParentLinkBox()
{
}

void TreeNode::InitialToParentLinkBox()
{
    Q_ASSERT(toParentLinkBox == nullptr);
    toParentLinkBox = new LinkBox(LinkBox::Role_ToParent, this);
    toParentLinkBox->setZValue(1);
    RearrangeToParentLinkBox();
}

void TreeNode::SetNodeName(const QString &value)
{
    nodeName->setPlainText(value);
    nodeName->setZValue(10);
    nodeName->setPos(-nodeName->boundingRect().width()/2, -nodeName->boundingRect().height()/2);
}

QString TreeNode::GetNodeName()
{
    return nodeName->toPlainText();
}

