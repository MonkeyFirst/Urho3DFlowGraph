#pragma once

#include <Urho3D\Urho3DAll.h>

#include "FlowNode.h"

typedef struct FlowNodeCreationParams
{
	String flowNodeName;
	Vector<String> inputPortsName;
	Vector<Variant> inputPortsVal;
	Vector<String> outputPortsName;
	Vector<Variant> outputPortsVal;

	void AddInputPort(String name, Variant val) 
	{
		inputPortsName.Push(name);
		inputPortsVal.Push(val);
	};

	void AddOutputPort(String name, Variant val) 
	{
		outputPortsName.Push(name);
		outputPortsVal.Push(val);
	};
} FlowNodeCreationParams;


/// Helper base class for user-defined flownodes exposed into flowgraph
class CustomFlowNodeComponent : public Component
{
    URHO3D_OBJECT(CustomFlowNodeComponent, Component);
public:
	friend class FlowGraphSystem;



    /// Construct.
    CustomFlowNodeComponent(Context* context);
    /// Destruct.
    virtual ~CustomFlowNodeComponent();

	static void RegisterObject(Context * context);
	 
	FlowNodeCreationParams& GetFlowNodeCreationParams();
	virtual SharedPtr<FlowNode> GetFlowNode();

	virtual void UpdateCustomFlowNode(FlowNode* flowNode);
protected:
	FlowNodeCreationParams creationParams_;
	SharedPtr<FlowNode> flowNode_;
};
