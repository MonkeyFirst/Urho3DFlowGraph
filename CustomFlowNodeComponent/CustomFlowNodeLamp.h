#pragma once

#include <Urho3D\Urho3DAll.h>
#include "CustomFlowNode.h"

/// Helper base class for user-defined game logic components that hooks up to update events and forwards them to virtual functions similar to ScriptInstance class.
class CustomFlowNodeLamp : public CustomFlowNodeComponent
{
	URHO3D_OBJECT(CustomFlowNodeLamp, CustomFlowNodeComponent);
public:

	enum InputPort 
	{
		Enable,
		LightColor
	};

	enum OutputPort
	{
		Changed
	};


	/// Construct.
	CustomFlowNodeLamp(Context* context);
	/// Destruct.
	virtual ~CustomFlowNodeLamp();

	static void RegisterObject(Context * context);
	
	void UpdateCustomFlowNode(FlowNode* flowNode);
};