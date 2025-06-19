#include "SdkLoader.h"

#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkQuad.h>
#include <vtkTriangleStrip.h>

#include <iostream>

SdkLoader::SdkLoader()
{
    _manager = fbxsdk::FbxManager::Create();
    if (!_manager)
    {
        std::cout << "FBX SDK Manager is null!\n";
        return;
    }
    FbxIOSettings* ios = FbxIOSettings::Create(_manager, IOSROOT);
    if (!ios)
    {
        std::cout << "FBX SDK Manager: IO Settings is null!\n";
        return;
    }
    _manager->SetIOSettings(ios);
    _scene = FbxScene::Create(_manager, "MyScene");
    if (!_scene)
    {
        std::cout << "FBX SDK Manager: Create scene failed!\n";
        return;
    }
    _importer = FbxImporter::Create(_manager, "");
    if (!_importer)
    {
        std::cout << "FBX SDK Manager: Importer is null!\n";
        return;
    }
}

SdkLoader::~SdkLoader()
{
    if (_manager)
        _manager->Destroy();
    if (_scene)
        _scene->Destroy();
    if (_importer)
        _importer->Destroy();
}

bool SdkLoader::importFile(const char* fileName)
{
    if (!_importer->Initialize(fileName, -1, _manager->GetIOSettings()))
    {
        std::cout << "FBX SDK Importer: Initialize failed!\n";
        return false;
    }
    if (!_importer->IsFBX())
    {
        std::cout << "FBX SDK Importer: Is DBX failed!\n";
        return false;
    }
    if (!_importer->Import(_scene))
    {
        std::cout << "FBX SDK Importer: Import Failed!\n";
        return false;
    }
    return true;
}

void SdkLoader::getMeshes(FbxNode* node)
{
    if (!node)
        return;
    int geometryCount = node->GetSrcObjectCount<FbxGeometry>();
    for (int i = 0; i < geometryCount; i++)
    {
        FbxGeometry* geometry = node->GetSrcObject<FbxGeometry>(i);
        if (geometry && geometry->GetAttributeType() == FbxNodeAttribute::eMesh)
        {
            //auto greenMt = MaterialHelper::CreateMaterial(Colors::Green);
            FbxMesh* mesh = geometry->GetNode()->GetMesh();
            //auto meshBuilder = new MeshBuilder(false, false, false);

            FbxLayer* layer = mesh->GetLayer(0);
            FbxLayerElementMaterial* pMaterialLayer = layer->GetMaterials();
            int numMatIndices = pMaterialLayer->GetIndexArray().GetCount();
            for (int k = 0; k < numMatIndices; k++)
            {
                int matIndex = pMaterialLayer->GetIndexArray()[k];
                FbxSurfaceMaterial* smat = mesh->GetNode()->GetMaterial(matIndex);
                if (smat->GetClassId().Is(FbxSurfaceLambert::ClassId))
                {
                    FbxSurfaceLambert* lam = (FbxSurfaceLambert*)smat;
                    FbxPropertyT<FbxDouble3> p = lam->Emissive;//Diffuse
                    FbxDouble3 color = p.Get();
                    //greenMt = MaterialHelper::CreateMaterial(Color::FromRgb((uchar)(255 * color[0]), (uchar)(255 * color[1]), (uchar)(255 * color[2])));
                    break;
                }
            }

            int polygonCount = mesh->GetPolygonCount();
            FbxVector4* controlPoints = mesh->GetControlPoints();
            for (int j = 0; j < polygonCount; j++)
            {
                int vertexCount = mesh->GetPolygonSize(j);
                //auto points = new List<Vector3>();
                if (vertexCount == 3)
                {
                    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
                    triangle->GetPointIds()->SetId(0, pointNum + 0);
                    triangle->GetPointIds()->SetId(1, pointNum + 1);
                    triangle->GetPointIds()->SetId(2, pointNum + 2);
                    pointNum += 3;
                    _cells->InsertNextCell(triangle);
                } else if (vertexCount == 4)
                {
                    vtkSmartPointer<vtkQuad> quad = vtkSmartPointer<vtkQuad>::New();
                    quad->GetPointIds()->SetId(0, pointNum + 0);
                    quad->GetPointIds()->SetId(1, pointNum + 1);
                    quad->GetPointIds()->SetId(2, pointNum + 2);
                    quad->GetPointIds()->SetId(3, pointNum + 3);
                    pointNum += 4;
                    _cells->InsertNextCell(quad);
                } else if (vertexCount > 4)
                {
                    vtkSmartPointer<vtkTriangleStrip> strip = vtkSmartPointer<vtkTriangleStrip>::New();
                    for (int k = 0; k < vertexCount; k++)
                        strip->GetPointIds()->SetId(k, pointNum + k);
                    pointNum += vertexCount;
                    _cells->InsertNextCell(strip);
                }

                for (int k = 0; k < vertexCount; k++)
                {
                    int vertexIndex = mesh->GetPolygonVertex(j, k);
                    FbxVector4 vertex = controlPoints[vertexIndex];
                    //points->Add(Vector3((float)vertex[0], (float)vertex[1], (float)vertex[2]));
                    _points->InsertNextPoint(vertex[0], vertex[1], vertex[2]);
                }
                //meshBuilder->AddPolygon(points);
            }
            //_modelGroup->Children->Add(new GeometryModel3D(ConvExt::ToWndMeshGeometry3D(meshBuilder->ToMesh(), true),greenMt));
        }
    }
    for (int i = 0; i < node->GetChildCount(); i++)
        getMeshes(node->GetChild(i));
}
