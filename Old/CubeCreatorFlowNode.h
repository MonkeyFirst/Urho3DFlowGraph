// Данная флоунода создает куб, когда на входном порту значение true (сигнал к созданию)
// также через входной порт нужно отправить указатель на сцену

#pragma once

#include "FlowNode.h"

class URHO3D_API CubeCreatorFlowNode : public FlowNode
{
    URHO3D_OBJECT(CubeCreatorFlowNode, FlowNode);

public:
    enum InputPort
    {
        IN_CREATE_SIGNAL = 0,
        IN_SCENE = 1
    };

    CubeCreatorFlowNode(Context* context);
    void Update(float timeStep);
};
