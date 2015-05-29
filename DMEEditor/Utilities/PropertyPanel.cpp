#include "PropertyPanel.h"

PropertyPanel::PropertyPanel(QWidget *parent) : QWidget(parent)
{
    setLayout(&layout);
}

PropertyPanel::~PropertyPanel()
{

}

void PropertyPanel::AddProperty(PropertyWidget *property)
{
    propertyWidgets.push_back(property);
    layout.addWidget(property);
}

void PropertyPanel::Clear()
{
    for(auto property : propertyWidgets)
    {
        layout.removeWidget(property);
        delete property;
    }

    propertyWidgets.clear();
}

