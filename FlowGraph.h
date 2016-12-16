#pragma once
#include <Urho3D/Urho3DAll.h>
#include "FlowNode.h"

class URHO3D_API FlowGraph : public Serializable
{
    URHO3D_OBJECT(FlowGraph, Object);

public:
    FlowGraph(Context* context);
    static void RegisterObject(Context* context);

    Vector<SharedPtr<FlowNode> > nodes_;
    Vector<Node*> updatedNodes_;

private:
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
};
