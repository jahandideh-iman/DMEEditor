#ifndef STRINGPROPERTY_H
#define STRINGPROPERTY_H

#include "PropertyWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

class StringProperty : public PropertyWidget
{
    Q_OBJECT
public:
    explicit StringProperty(QString label, QString initialValue, QObject* obj, const char* slot);
    ~StringProperty();

signals:

public slots:

private:
    QLabel properyLabel;
    QLineEdit propertyLineEdit;

    QGridLayout layout;
};

#endif // STRINGPROPERTY_H
