#ifndef MENUCONTRIBUTER
#define MENUCONTRIBUTER

#include <QMenu>

class MenuContributer
{
public:
    virtual void ContributeToMenu(QMenu *menu) = 0;
};

#endif // MENUCONTRIBUTER

