/*
    Флаунада (блок).
    TODO: переименовать в FlowBlock.
*/

#pragma once
#include <Urho3D/Urho3DAll.h>
#include "FlowPort.h"

class FlowInputPort;
class FlowOutputPort;

class URHO3D_API FlowNode : public Serializable
{
    URHO3D_OBJECT(FlowNode, Serializable);

public:
    FlowNode(Context* context);

    // Эта функция вызывается из класса FlowGraph.
    // Гарантируется, что апдейт для данной ноды будет выполнен
    // только после апдейта нод, присоединенных к входным портам.
    virtual void Update(float timeStep);

    // Порты флауноды.
    Vector<SharedPtr<FlowInputPort> > inputs_;
    Vector<SharedPtr<FlowOutputPort> > outputs_;

    // Требуется ли выполнить апдейт для этой флауноды.
    bool needUpdate_ = true;

    // Функция проверяет все входящие порты и возвращает true,
    // если все входящие флоуноды обновлены.
    bool IsInputNodesUpdated();

    // СОздание портов, потом надо передавать еще и тип.
    void CreateInputPort(const String& name, int type);
    void CreateOutputPort(const String& name, int type);

    // Для визуального редактора - заголовок и координаты на холсте.
    // Пока не используются.
    String name_;
    Vector2 position_;
};
