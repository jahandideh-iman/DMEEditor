#include "StringProperty.h"

StringProperty::StringProperty(QString label, QString initialValue, QObject* obj, const char* slot)
{
    setLayout(&layout);
    properyLabel.setText(label+ " ");
    layout.addWidget(&properyLabel,0,0);
    layout.addWidget(&propertyLineEdit,0,1);
    propertyLineEdit.setText(initialValue);
    connect(&propertyLineEdit,SIGNAL(textChanged(const QString & )),obj,slot);
}

StringProperty::~StringProperty()
{

}

