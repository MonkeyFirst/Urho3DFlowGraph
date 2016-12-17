#include "StarterFlowNode.h"

StarterFlowNode::StarterFlowNode(Context* context) :
    FlowNode(context)
{
}

void StarterFlowNode::Update(float timeStep)
{
    // Если это первый апдейт, то пишем true в выходной порт.
    if (!sended_)
    {
        outputs_["Started"].data_ = true;
        sended_ = true;
        return;
    }
    
    // Все остальное время пишем в порт false.
    outputs_["Started"].data_ = false;
}