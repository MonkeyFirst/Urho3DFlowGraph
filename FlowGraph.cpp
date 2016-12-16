#include "FlowGraph.h"

FlowGraph::FlowGraph(Context* context) :
    Serializable(context)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(FlowGraph, HandleUpdate));
}

void FlowGraph::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Как-то надо запретить создание нод в процессе апдейта.
    for (Vector<SharedPtr<FlowNode> >::Iterator i = nodes_.Begin(); i != nodes_.End(); ++i)
    {
        FlowNode* node = *i;
        node->Update(timeStep);
    }
}

