#ifndef MYVTKITEM_H
#define MYVTKITEM_H

#include <QQuickVTKItem.h>
#include <vtkNew.h>
#include <vtkActor.h>
#include <vtkObject.h>
#include <vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkObjectFactory.h>

#include "SdkLoader.h"

struct MyVtkItem : QQuickVTKItem
{
    Q_OBJECT
public:

    struct Data : vtkObject
    {
        static Data* New();
        vtkTypeMacro(Data, vtkObject);

        //vtkNew<vtkBoxWidget> boxWidget;
    };

    struct Callback : vtkCommand
    {
        static Callback* New();
        void Execute(vtkObject* caller, unsigned long, void*) override;
    };

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;

    SdkLoader* _sdkLoader = nullptr;

    vtkNew<vtkActor> _actor;
    vtkNew<vtkPolyDataMapper> _mapper;
    vtkNew<vtkRenderer> _renderer;
    vtkNew<vtkPolyData> _polyData;
};

Q_DECLARE_METATYPE(MyVtkItem);

#endif // MYVTKITEM_H
