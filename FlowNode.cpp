#include "FlowNode.h"

Variant FlowNodePort::ReadData()
{
    if (!connectedPort_.Expired())
        return connectedPort_->data_;

    return data_;
}


FlowNode::FlowNode(Context* context) :
    Serializable(context)
{
}

void FlowNode::Update(float timeStep)
{
}

bool FlowNode::IsUpdated()
{
    // Была ли флоунода выполнена в текущем кадре.
    return (GetSubsystem<Time>()->GetFrameNumber() == lastUpdateFrameNumber_);
}

bool FlowNode::IsInputNodesUpdated()
{
    for (HashMap<StringHash, FlowNodePort>::Iterator i = inputs_.Begin(); i != inputs_.End(); ++i)
    {
        FlowNodePort port = i->second_;

        // Если подключена входящая нода и она не обновлена, то прекращаем
        if (!port.connectedPort_.Expired() && !port.connectedPort_->node_->IsUpdated())
            return false;
    }
    
    return true;
}