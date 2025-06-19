#ifndef MYVTKITEM_H
#define MYVTKITEM_H

#include <QQuickVTKItem.h>
#include <vtkNew.h>
#include <vtkObject.h>
#include <vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkObjectFactory.h>

#include "SdkLoader.h"

struct MyVtkItem : QQuickVTKItem
{
    struct Data : vtkObject
    {
        static Data* New();
        vtkTypeMacro(Data, vtkObject);

        vtkNew<vtkBoxWidget> boxWidget;
    };

    struct Callback : vtkCommand
    {
        static Callback* New();
        void Execute(vtkObject* caller, unsigned long, void*) override;
    };

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;

    SdkLoader *sdkLoader = nullptr;
};

#endif // MYVTKITEM_H
