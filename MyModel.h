#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QMetaType>
#include <QUrl>

class MyVtkItem;

class MyModel : public QObject
{
    Q_OBJECT
public:
    MyVtkItem *_vtkItem = nullptr;
public slots:
    void handleFileSelected(const QUrl &fileUrl);
};
Q_DECLARE_METATYPE(MyModel);

#endif // MYMODEL_H
