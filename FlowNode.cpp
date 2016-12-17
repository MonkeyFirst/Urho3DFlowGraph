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