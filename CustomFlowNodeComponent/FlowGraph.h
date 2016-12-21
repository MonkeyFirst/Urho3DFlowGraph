/*
    FlowGraph выполняет апдейт всех флаунод в правильном порядке.
*/

#pragma once
#include <Urho3D/Urho3DAll.h>

#include "FlowGraphSystem.h"
#include "FlowNode.h"

class URHO3D_API FlowGraph : public Serializable
{
    URHO3D_OBJECT(FlowGraph, Serializable);

	friend class FlowGraphSystem;

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

	// Выкл/Вкл фрау для Update
	void SetActive(bool isActive) { isActive_ = isActive; };
	bool IsActive() { return isActive_; };
	void SetName(String name) { name_ = name; };
	String GetName() { return name_; };

protected:
	void Update(float timeStep);
	
	bool isActive_;
	String name_;

private:
    //void HandleUpdate(StringHash eventType, VariantMap& eventData);
};
