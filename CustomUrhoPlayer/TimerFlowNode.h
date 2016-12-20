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
		Active,
		Period,
		MaxTicks,
		Reset,
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

private:
	float elapsedTime;
	bool defaultsCollected_;

	struct 
	{
		bool active_;
		float preriod_;
		int maxticks_;
	} timerDefaults;


	void CollectDefaults();
	void ResetToDefaults();
};