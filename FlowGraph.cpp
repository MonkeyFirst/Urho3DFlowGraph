#include "FlowGraph.h"

FlowGraph::FlowGraph(Context* context) :
    Serializable(context)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(FlowGraph, HandleUpdate));
}

void FlowGraph::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Цикл, пока код всех флоунод не будет выполнен.
    while (true)
    {
        // Остались ли ще не выполненные ноды.
        // В этом случае цикл продолжится.
        bool isNotUpdated = false;

        // Цикл по всем флоунодам в графе.
        for (Vector<SharedPtr<FlowNode> >::Iterator i = nodes_.Begin(); i != nodes_.End(); ++i)
        {
            FlowNode* node = *i;

            // Нода уже обновлена, не трогаем ее.
            if (node->IsUpdated())
                continue;

            // У ноды не обновлены входящие соединения. Пока не выполняем текущую ноду,
            // а ждем одновления входящих нод.
            if (!node->IsInputNodesUpdated())
            {
                isNotUpdated = true;
                continue;
            }

            // Входящие ноды обновлены, все нормально.
            node->Update(timeStep);

            // Помечаем ноду как выполненную.
            node->lastUpdateFrameNumber_ = GetSubsystem<Time>()->GetFrameNumber();
        }

        // Прерываем цикл, когда не было найдено необновленных нод.
        if (!isNotUpdated)
            break;
    }
}

