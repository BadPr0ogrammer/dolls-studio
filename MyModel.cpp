#include "MyModel.h"
#include "MyVtkItem.h"

void MyModel::handleFileSelected(const QUrl &fileUrl)
{
    delete _vtkItem->_sdkLoader;
    _vtkItem->_sdkLoader = new SdkLoader();
    if (_vtkItem->_sdkLoader->importFile(fileUrl.toLocalFile().toUtf8())) {
        _vtkItem->_sdkLoader->_pointNum = 0;
        _vtkItem->_sdkLoader->getMeshes((FbxNode*)_vtkItem->_sdkLoader->_scene);

        _vtkItem->_polyData->SetPoints(_vtkItem->_sdkLoader->_points);
        _vtkItem->_polyData->SetPolys(_vtkItem->_sdkLoader->_cells);
    } else {
        delete _vtkItem->_sdkLoader;
        _vtkItem->_sdkLoader = nullptr;
    }
}
