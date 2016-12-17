#pragma once
#include <Urho3D/Urho3DAll.h>

class FlowNode;

// Входный и выходной порт описываются одинаковой структурой.
struct FlowNodePort
{
    // Данные, которые содержатся в порте. Это может быть переменная любого типа.
    // Для входного порта эти данные пользователь может указать вручную в редакторе.
    Variant data_;

    // Нода, которая присоединена к порту. Может отсутсвовать.
    WeakPtr<FlowNode> connectedNode_;

    // Функция используется для входного порта.
    // Если есть входящее подключение (connetedNode_ не null), то обращается к подключенной ноде
    // и возвращает данные из ее выходного порта.
    // Если к порту ничег оне подключено, но возвращает data_ (то есть значение, заданное пользователем).
    // Пока этого не сделано, просто возвращает data_;
    Variant ReadData();
};

class URHO3D_API FlowNode : public Serializable
{
    URHO3D_OBJECT(FlowNode, Serializable);

public:
    FlowNode(Context* context);

    // Эта функция вызывается из класса FlowGraph.
    // Гарантируется, что апдейт для данной ноды будет вызван
    // только после апдейта дочерних нод, которые формируют
    // входные данные для данной ноды.
    virtual void Update(float timeStep);

    // Входные порты.
    HashMap<StringHash, FlowNodePort> inputs_;

    // Выходные порты.
    HashMap<StringHash, FlowNodePort> outputs_;

    // Кадр, в котором в последний раз флоунода была выполнена.
    // Это значение хранится для того, чтобы знать была ли нода обновлена в текущем кадре.
    unsigned lastUpdateFrameNumber_ = M_MAX_UNSIGNED;

    // Обновлена ли уже нода в данном кадре. Нода может быть обновлена только после того,
    // как будут обновлены все входящие флоуноды.
    bool IsUpdated();

    // Функция проверяет все входящие порты и возвращает true,
    // если все входящие флоуноды обновлены в этом кадре.
    bool IsInputNodesUpdated();

    // Для визуального редактора - заголово и координаты на холсте.
    // Пока не используются.
    String name_;
    Vector2 position_;
};
