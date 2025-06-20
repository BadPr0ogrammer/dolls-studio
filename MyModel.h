#pragma once

#include <QObject>
#include <QMetaType>
#include <QUrl>

class MyVtkItem;

class ModelAc : public QObject
{
    Q_OBJECT
public:
    MyVtkItem *_vtkItem = nullptr;
public slots:
    void handleFileSelected(const QUrl &fileUrl);
};
Q_DECLARE_METATYPE(ModelAc);


