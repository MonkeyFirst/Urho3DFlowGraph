/*
    Соединение (дуга, ребро) между портами двух флаунод (блоков).
*/

#pragma once
#include <Urho3D/Urho3DAll.h>
#include "FlowPort.h"

class FlowOutputPort;
class FlowInputPort;

class URHO3D_API FlowEdge : public Object
{
    URHO3D_OBJECT(FlowEdge, Object);

public:
    FlowEdge(Context* context);

    // Порты, которые соединены дугой.
    // Соединение всегда однонаправленное.
    WeakPtr<FlowOutputPort> fromPort_;
    WeakPtr<FlowInputPort> toPort_;
};
