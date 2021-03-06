#include "FlowGraph.h"

namespace Urho3D
{

FlowGraph::FlowGraph(Context* context) :
    Serializable(context)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(FlowGraph, HandleUpdate));
}

void FlowGraph::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    //URHO3D_LOGWARNING("FlowGraph::HandleUpdate");

    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Все ноды помечаются как неапдейченные.
    for (Vector<SharedPtr<FlowNode> >::Iterator i = nodes_.Begin(); i != nodes_.End(); ++i)
    {
        FlowNode* node = *i;
        node->needUpdate_ = true;
    }

    // Цикл, пока код всех флоунод не будет выполнен.
    while (true)
    {
        // Остались ли еще требующие апдейта флауноды.
        // В этом случае цикл продолжится.
        bool existsNotUpdated = false;

        // Цикл по всем флоунодам в графе.
        for (Vector<SharedPtr<FlowNode> >::Iterator i = nodes_.Begin(); i != nodes_.End(); ++i)
        {
            FlowNode* node = *i;

            // Нода уже обновлена, не трогаем ее.
            if (node->needUpdate_ == false)
                continue;

            // У ноды не обновлены входящие соединения. Пока не выполняем текущую ноду,
            // а ждем одновления входящих нод.
            if (!node->IsInputNodesUpdated())
            {
                existsNotUpdated = true;
                continue;
            }

            // Входящие ноды обновлены, все нормально. Можно апдейтить и эту ноду.
            node->Update(timeStep);

            // Помечаем ноду как выполненную.
            node->needUpdate_ = false;
        }

        // Прерываем цикл, когда не было найдено необновленных нод.
        if (!existsNotUpdated)
            break;
    }
}

// Тут надо сделать проверки на совпадение типов портов и отсутствие зацикливания.
bool FlowGraph::Connect(FlowOutputPort* fromPort, FlowInputPort* toPort)
{
    //URHO3D_LOGWARNING("FlowGraph::Connect");
    SharedPtr<FlowEdge> link(new FlowEdge(context_));
    link->fromPort_ = fromPort;
    link->toPort_ = toPort;
    fromPort->edge_ = link;
    toPort->edge_ = link;
    // Указатель на дугу надо хранить, чтоб не самоуничтожилась.
    edges_.Push(link);
    return true;
}

void FlowGraph::AddFlowNode(FlowNode* node)
{
    URHO3D_LOGWARNING("FlowGraph::AddFlowNode");
    nodes_.Push(SharedPtr<FlowNode>(node));
}

}