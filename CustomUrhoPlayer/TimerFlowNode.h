#pragma once

// Данная флоунода тамер

#pragma once

#include "FlowNode.h"

class URHO3D_API TimerFlowNode : public FlowNode
{
	URHO3D_OBJECT(TimerFlowNode, FlowNode);

public:

	enum InputPort
	{
		Period,
		MaxTicks,
		InputLast
	};

	enum OutputPort 
	{
		TimerEvent,
		OutputLast
	};

	TimerFlowNode(Context* context);
	void Update(float timeStep);
	bool CheckTime(float period, float timeStep);

	float elapsedTime;
};