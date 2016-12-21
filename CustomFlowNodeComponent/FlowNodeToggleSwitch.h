#pragma once

// Данная флоунода тумблер

#pragma once

#include "FlowNode.h"

class URHO3D_API ToggleSwitchFlowNode : public FlowNode
{
	URHO3D_OBJECT(ToggleSwitchFlowNode, FlowNode);

public:

	enum InputPort
	{
		Toggle,
		InputLast
	};

	enum OutputPort
	{
		TurnOn,
		TurnOff,
		OutputLast
	};

	ToggleSwitchFlowNode(Context* context);
	void Update(float timeStep);

private:
	bool flag_;

};