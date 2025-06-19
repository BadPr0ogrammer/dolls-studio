#include "MyVtkItem.h"

#include <QVTKRenderWindowAdapter.h>

#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkActor.h>
#include <vtkBoxWidget.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
//#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkProp3D.h>

#include "SdkLoader.h"

vtkStandardNewMacro(MyVtkItem::Data);
vtkStandardNewMacro(MyVtkItem::Callback);

void MyVtkItem::Callback::Execute(vtkObject* caller, unsigned long, void*)
{
    /*
    vtkNew<vtkTransform> t;
    auto widget = reinterpret_cast<vtkBoxWidget*>(caller);
    widget->GetTransform(t);
    widget->GetProp3D()->SetUserTransform(t);
*/
}

MyVtkItem::vtkUserData MyVtkItem::initializeVTK(vtkRenderWindow* renderWindow)
{
    sdkLoader = new SdkLoader();
    sdkLoader->importFile("RumbaDancing.fbx");
    sdkLoader->getMeshes((FbxNode*)sdkLoader->_scene);

    vtkNew<Data> vtk;
    vtkNew<vtkActor> actor;

    vtkNew<vtkPolyDataMapper> mapper;
    actor->SetMapper(mapper);

    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(sdkLoader->_points);
    polyData->SetPolys(sdkLoader->_cells);

    mapper->SetInputData(polyData);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderer->SetBackground(1,1,1);

    renderWindow->AddRenderer(renderer);
    renderWindow->SetMultiSamples(16);

    vtk->boxWidget->SetInteractor(renderWindow->GetInteractor());
    vtk->boxWidget->SetPlaceFactor(1.25);
    vtk->boxWidget->SetProp3D(actor);
    vtk->boxWidget->PlaceWidget();
    vtk->boxWidget->On();

    //vtkNew<Callback> callback;
    //vtk->boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

    return vtk;
}
