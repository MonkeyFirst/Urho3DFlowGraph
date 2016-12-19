#include "StarterFlowNode.h"

namespace Urho3D
{

StarterFlowNode::StarterFlowNode(Context* context) :
    FlowNode(context)
{
    // Создаем выходной порт.
    CreateOutputPort("Start Signal", VAR_BOOL);
}

void StarterFlowNode::Update(float timeStep)
{
    // Если это первый апдейт, то пишем true в выходной порт.
    if (!sended_)
    {
        outputs_[OUT_START_SIGNAL]->data_ = true;
        sended_ = true;
        return;
    }
    
    // Все остальное время пишем в порт false.
    outputs_[OUT_START_SIGNAL]->data_ = false;
}

}