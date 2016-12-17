// Данная флоунода создает куб, когда на входном порту значение true (сигнал к соданию)
// также через входной порт нужно отправить указатель на сцену

#pragma once

#include "FlowNode.h"

class URHO3D_API CubeCreatorFlowNode : public FlowNode
{
    URHO3D_OBJECT(CubeCreatorFlowNode, FlowNode);

public:
    CubeCreatorFlowNode(Context* context);
    void Update(float timeStep);
};
