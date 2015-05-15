#include "Attachment.h"
#include "AttachBox.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "Application.h"
#include "BehaviorTreeGraphicsScene.h"
#include "Application.h"
#include "BehaviorTreeEditor.h"

Attachment::Attachment(AttachBox *parent, AttachBox *child)
{
    this->child = child;
    this->parent = parent;
    line = new QGraphicsLineItem(QLineF(parent->mapToScene(0,0),child->mapToScene(0,0)),this);
    child->SetAttachment(this);
    parent->SetAttachment(this);
}

Attachment::~Attachment()
{
    child->SetAttachment(nullptr);
    parent->SetAttachment(nullptr);
    delete line;
}

void Attachment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    line->setLine(QLineF(parent->mapToScene(0,0),child->mapToScene(0,0)));
}

QRectF Attachment::boundingRect() const
{
    return line->boundingRect();
}

void Attachment::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Detach", this, SLOT(Dettach()));
}

void Attachment::Dettach()
{
    ((BehaviorTreeEditor*) Application::Get()->GetEditor())->Detach(this);
}

