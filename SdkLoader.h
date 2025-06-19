#pragma once

#include <fbxsdk.h>

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

#include <vector>

class SdkLoader
{
public:
    fbxsdk::FbxManager* _manager = NULL;
    fbxsdk::FbxScene* _scene = NULL;
    fbxsdk::FbxImporter* _importer = NULL;

    vtkNew<vtkPoints> _points;
    vtkNew<vtkCellArray> _cells;
    int pointNum = 0;

    SdkLoader();
    ~SdkLoader();

    bool importFile(const char* fileName);
    void getMeshes(FbxNode* node);
};
