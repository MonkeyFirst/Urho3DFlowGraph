#include "CubeCreatorFlowNode.h"

namespace Urho3D
{

CubeCreatorFlowNode::CubeCreatorFlowNode(Context* context) :
    FlowNode(context)
{
    // Создаем входные порты.
    CreateInputPort("Create Signal", VAR_BOOL);
    CreateInputPort("Scene", VAR_VOIDPTR);
}

void CubeCreatorFlowNode::Update(float timeStep)
{
    //URHO3D_LOGWARNING("CubeCreatorFlowNode::Update");

    // Получаем сигнал к действию.
    bool signal = inputs_[IN_CREATE_SIGNAL]->ReadData().GetBool();

    if (!signal)
        return;

    // Получаем указатель на сцену из входного порта.
    Scene* scene = static_cast<Scene*>(inputs_[IN_SCENE]->ReadData().GetVoidPtr());

    // Создаем куб в некоторой окрестности от нуля.
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Node* cubeNode = scene->CreateChild();
    cubeNode->SetPosition(Vector3(Random(-2.5f, 2.5f), 0.5f, Random(-2.5f, 2.5f)));
    cubeNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
    cubeNode->SetScale(1.0f);
    StaticModel* cubeObject = cubeNode->CreateComponent<StaticModel>();
    cubeObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    cubeObject->SetCastShadows(true);
}

}