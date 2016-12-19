/*
    Разъем на флауноде.
*/

#pragma once
#include <Urho3D/Urho3DAll.h>
#include "FlowNode.h"
#include "FlowEdge.h"

class FlowNode;
class FlowEdge;

class URHO3D_API FlowOutputPort : public Object
{
    URHO3D_OBJECT(FlowOutputPort, Object);

public:
    FlowOutputPort(Context* context);

    // Текстовое имя порта отображается в редакторе.
    String name_;

    // Флаунода, на которой находится данный порт.
    WeakPtr<FlowNode> node_;

    // Данные, которые хранятся в порту. Для входного порта
    // эти данные пользователь может задать вручную в редакторе.
    // Для выходного порта сюда записываеся результат выполнения флауноды.
    Variant data_;

    // Соединение с портом другой ноды. Может отсутствовать.
    WeakPtr<FlowEdge> edge_;
};

// Входной порт отличается от выходного функцией ReadData().
class URHO3D_API FlowInputPort : public FlowOutputPort
{
    URHO3D_OBJECT(FlowInputPort, FlowOutputPort);

public:
    FlowInputPort(Context* context);

    // Если есть соединение с другим портом (входящее), то эта функция
    // возвращает данные присоединенной ноды (выходящие).
    // Если к порту ничего не подключено, то просто возвращает data_
    // (то есть значение, заданное пользователем).
    Variant ReadData();
};
