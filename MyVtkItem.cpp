#include "MyVtkItem.h"
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
    vtkNew<Data> vtk;
    _actor->SetMapper(_mapper);

    _mapper->SetInputData(_polyData);

    _renderer->AddActor(_actor);
    _renderer->ResetCamera();
    _renderer->SetBackground(0.2,0.2,0.2);

    renderWindow->AddRenderer(_renderer);
    renderWindow->SetMultiSamples(16);
    /*
    vtk->boxWidget->SetInteractor(renderWindow->GetInteractor());
    vtk->boxWidget->SetPlaceFactor(1.25);
    vtk->boxWidget->SetProp3D(_actor);
    vtk->boxWidget->PlaceWidget();
    vtk->boxWidget->On();
    */
    //vtkNew<Callback> callback;
    //vtk->boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

    return vtk;
}
