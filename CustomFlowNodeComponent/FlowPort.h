/*
    Разъем на флауноде.
*/

#pragma once
#include <Urho3D/Urho3DAll.h>
#include "FlowNode.h"
#include "FlowEdge.h"

class FlowNode;
class FlowEdge;

static const int VAR_ANY = -1;

class URHO3D_API FlowOutputPort : public Object
{
    URHO3D_OBJECT(FlowOutputPort, Object);

public:
	friend class FlowNode;

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

    // Ожидаемый тип переменной. Он может быть любым из "enum VariantType" или -1, если разрешена переменная любого типа.
    int type_;

	// Флаг говорящий о том что данный порт был кем-то посещен без цели записать в порт данные.
	//void Visited() { visited_ = true; visitedNum_++; };
	//bool IsVisited() { return visited_; };

protected:

	//// Нода сама должна сбрасывать флаг посещений у порта после Update в графе
	//void ResetVisited() { visited_ = false; visitedNum_ = 0; };

	//bool visited_;
	//unsigned int visitedNum_;


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
