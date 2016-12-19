// Пример флоуноды, которая управляет камерой.
// На вход подается указатель на ноду камеры, которой нужно управлять и чувствительность мышки.
// Эти значения пользователь должен задавать в редакторе
// (ну указатель не укажет конечно, камеру перетащит на ноду или имя ноды/айди надо задавать), но пока все задается в коде.

#pragma once
#include "FlowNode.h"

class URHO3D_API CameraControllerFlowNode : public FlowNode
{
    URHO3D_OBJECT(CameraControllerFlowNode, FlowNode);

public:
    CameraControllerFlowNode(Context* context);
    void Update(float timeStep);

    enum InputPort
    {
        IN_CAMERA_NODE = 0,
        IN_MOUSE_SENSITIVITY = 1
    };

    float yaw_ = 0.0f;
    float pitch_ = 45.0f;
};
