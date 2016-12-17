#include "FlowNode.h"

Variant FlowNodePort::ReadData()
{
    if (!connectedNode_.Expired()) // Если есть подключенная флоунода входная нода
    {
        // Тут надо получить выходные данные входной ноды, но пока этого нет.
    }

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

        // Если подключена входящая нода и она нге обновлена, то прекращаем
        if (!port.connectedNode_.Expired() && !port.connectedNode_ - IsUpdated())
            return false;
    }
    
    return true;
}