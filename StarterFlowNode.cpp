#include "StarterFlowNode.h"

StarterFlowNode::StarterFlowNode(Context* context) :
    FlowNode(context)
{
    // Создаем выходной порт.
    SharedPtr<FlowOutputPort> signalOutputPort(new FlowOutputPort(context));
    signalOutputPort->node_ = this;
    outputs_["Start"] = signalOutputPort;
}

void StarterFlowNode::Update(float timeStep)
{
    // Если это первый апдейт, то пишем true в выходной порт.
    if (!sended_)
    {
        outputs_["Start"]->data_ = true;
        sended_ = true;
        return;
    }
    
    // Все остальное время пишем в порт false.
    outputs_["Start"]->data_ = false;
}