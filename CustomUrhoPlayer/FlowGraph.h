/*
    FlowGraph выполняет апдейт всех флаунод в правильном порядке.
*/

#pragma once
#include <Urho3D/Urho3DAll.h>
#include "FlowNode.h"

namespace Urho3D
{

class URHO3D_API FlowGraph : public Serializable
{
    URHO3D_OBJECT(FlowGraph, Serializable);

public:
    FlowGraph(Context* context);
    static void RegisterObject(Context* context);

    // Все флаунады.
    Vector<SharedPtr<FlowNode> > nodes_;
    
    // Все соединения между флаунодами.
    // Этот список нужен, чтобы SharedPtr не самоудалялись.
    Vector<SharedPtr<FlowEdge> > edges_;

    // Создать соединение портов.
    bool Connect(FlowOutputPort* fromPort, FlowInputPort* toPort);

    void AddFlowNode(FlowNode* node);

private:
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
};

}