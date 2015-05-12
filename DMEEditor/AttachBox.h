#ifndef ATTACHBOX_H
#define ATTACHBOX_H

#include <QGraphicsRectItem>


class AttachBox : public QGraphicsRectItem
{
public:
    enum Role{Role_Parent, Role_Child};
public:
    AttachBox(Role role,QGraphicsItem *parent = 0);
    ~AttachBox();

    Role GetRole();

private:
    Role role;
};

#endif // ATTACHBOX_H
