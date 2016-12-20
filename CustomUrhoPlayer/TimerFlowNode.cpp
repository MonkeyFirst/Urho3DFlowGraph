#include "TimerFlowNode.h"

TimerFlowNode::TimerFlowNode(Context * context) : 
	FlowNode(context),
	elapsedTime(0.0f)
{
	
	inputs_.Resize(InputLast);
	outputs_.Resize(OutputLast);

	// Создаем входные порты.
	SharedPtr<FlowInputPort> periodInputPort(new FlowInputPort(context));
	periodInputPort->node_ = this;
	periodInputPort->data_ = Variant(1.0f); // default value
	
	inputs_[Period] = periodInputPort;

	SharedPtr<FlowInputPort> maxTicksInputPort(new FlowInputPort(context));
	maxTicksInputPort->node_ = this;
	maxTicksInputPort->data_ = Variant(5); // default value
	inputs_[MaxTicks] = maxTicksInputPort;

	SharedPtr<FlowOutputPort> timerEventInputPort(new FlowOutputPort(context));
	timerEventInputPort->node_ = this;
	outputs_[TimerEvent] = timerEventInputPort;

}

void TimerFlowNode::Update(float timeStep)
{
	float period = inputs_[Period]->ReadData().GetFloat();
	int ticks = inputs_[MaxTicks]->ReadData().GetInt();

	if (ticks == -1) // infinity case
	{
		CheckTime(period, timeStep);
	}
	else if (ticks >= 1) // countdown timer case
	{
		if (CheckTime(period, timeStep))
			inputs_[MaxTicks]->data_ = Variant(--ticks);
	}
	else // nothing send case
	{
		outputs_[TimerEvent]->data_ = false;
	}
}

bool TimerFlowNode::CheckTime(float period, float timeStep)
{
	bool fired = false;
	
	if (elapsedTime > period)
	{
		elapsedTime = 0.0f;

		outputs_[TimerEvent]->data_ = true;

		fired = true;
	}
	else
	{
		elapsedTime += timeStep;
		outputs_[TimerEvent]->data_ = false;
	}

	return fired;
}
