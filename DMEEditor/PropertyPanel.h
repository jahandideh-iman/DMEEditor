#ifndef PROPERTYPANEL_H
#define PROPERTYPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "PropertyWidget.h"

class PropertyPanel : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyPanel(QWidget *parent = 0);
    ~PropertyPanel();

    void AddProperty(PropertyWidget* property);

    void Clear();


private:
    QVBoxLayout layout;

    QVector<PropertyWidget*> propertyWidgets;
signals:

public slots:
};

#endif // PROPERTYPANEL_H
