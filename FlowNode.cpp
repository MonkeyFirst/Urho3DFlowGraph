#include "FlowNode.h"

FlowNode::FlowNode(Context* context) :
    Serializable(context)
{
}

void FlowNode::Update(float timeStep)
{
}

bool FlowNode::IsInputNodesUpdated()
{
    for (HashMap<StringHash, SharedPtr<FlowInputPort> >::Iterator i = inputs_.Begin(); i != inputs_.End(); ++i)
    {
        FlowInputPort* port = i->second_;

        // Если к порту ничего не подключено, то возвращаем true.
        if (port->edge_.Expired())
            return true;

        // Проверка, что что-то пошло не так. Соединение есть, но порта, к которому оно подключено, нет.
        // Равносильно тому, что соединений нет.
        if (port->edge_->fromPort_.Expired())
            return true;

        // Содениенение есть, порт есть, а ноды нет. Вообще это внештатная ситуация, проверка на всякий случй.
        if (port->edge_->fromPort_->node_)
            return true;

        return !port->edge_->fromPort_->node_->needUpdate_;
    }

    return true;
}