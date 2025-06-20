#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QSurfaceFormat>
#include <QQmlContext>
#include <QQuickVTKItem.h>

#include "MyVtkItem.h"
#include "MyModel.h"
#include "TreeModel.h"

#include <iostream>

int main(int argc, char* argv[])
{
    QQuickVTKItem::setGraphicsApi();

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<MyVtkItem>("MyModule", 1, 0, "MyVtkItem");
    QQmlApplicationEngine engine;
    MyModel myModel;
    engine.rootContext()->setContextProperty("MyModel", &myModel);
    TreeModel treeModel;
    engine.rootContext()->setContextProperty("myTreeModel", &treeModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        std::cout << "Engine Root Objects is Empty!\n";
        return -1;
    }
    QObject *vtk = engine.rootObjects()[0]->findChild<QObject*>("myVtkItem");
    if (!vtk) {
        std::cout << "Find Child \"myVtkItem\" is null!\n";
        return -1;
    }
    myModel._vtkItem = (MyVtkItem *)vtk;

    return app.exec();
}
