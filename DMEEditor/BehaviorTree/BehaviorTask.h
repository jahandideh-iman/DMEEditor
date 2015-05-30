#ifndef BEHAVIORTASK_H
#define BEHAVIORTASK_H

#include "TreeUtilities/TreeNode.h"

class BehaviorTask : public TreeNode
{
public:
    BehaviorTask();
    virtual ~BehaviorTask();

    virtual LinkBox *GetAnEmptyToChildAttachBox() = 0;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void OnLinkBoxSelected(LinkBox *selected) override;

    void Remove() override;

protected:
    void RearrangeToParentLinkBox() override;
    void RearrangeToChildLinkBoxes() override;

    virtual void InitialPropertyWidgets() ;
};

#endif // BEHAVIORTASK_H
