#pragma once

#include <fbxsdk.h>

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

class SdkLoader
{
public:
    fbxsdk::FbxManager* _manager = NULL;
    fbxsdk::FbxScene* _scene = NULL;
    fbxsdk::FbxImporter* _importer = NULL;

    vtkNew<vtkPoints> _points;
    vtkNew<vtkCellArray> _cells;
    int _pointNum = 0;

    SdkLoader();
    ~SdkLoader();

    bool importFile(const char* fileName);
    void getMeshes(FbxNode* node);
};
