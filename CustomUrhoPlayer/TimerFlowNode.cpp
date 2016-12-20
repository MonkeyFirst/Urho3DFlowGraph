#include "TimerFlowNode.h"

TimerFlowNode::TimerFlowNode(Context * context) : 
	FlowNode(context),
	elapsedTime(0.0f),
	defaultsCollected_(false)
{
	
	inputs_.Resize(InputLast);
	outputs_.Resize(OutputLast);

	// Создаем входные порты.
	SharedPtr<FlowInputPort> activeInputPort(new FlowInputPort(context));
	activeInputPort->node_ = this;
	activeInputPort->data_ = true; // default value

	inputs_[Active] = activeInputPort;

	SharedPtr<FlowInputPort> periodInputPort(new FlowInputPort(context));
	periodInputPort->node_ = this;
	periodInputPort->data_ = Variant(1.0f); // default value
	
	inputs_[Period] = periodInputPort;

	SharedPtr<FlowInputPort> maxTicksInputPort(new FlowInputPort(context));
	maxTicksInputPort->node_ = this;
	maxTicksInputPort->data_ = Variant(5); // default value
	inputs_[MaxTicks] = maxTicksInputPort;

	SharedPtr<FlowInputPort> resetInputPort(new FlowInputPort(context));
	resetInputPort->node_ = this;
	resetInputPort->data_ = false; // default value
	inputs_[Reset] = resetInputPort;


	SharedPtr<FlowOutputPort> timerEventInputPort(new FlowOutputPort(context));
	timerEventInputPort->node_ = this;
	outputs_[TimerEvent] = timerEventInputPort;

}

void TimerFlowNode::Update(float timeStep)
{
	float period = inputs_[Period]->ReadData().GetFloat();
	int ticks = inputs_[MaxTicks]->ReadData().GetInt();
	bool active = inputs_[Active]->ReadData().GetBool();
	bool resetToDefaults = inputs_[Reset]->ReadData().GetBool();

	// Get all default for this instance of timer on First Update
	if (!defaultsCollected_) 
		CollectDefaults();

	// If fired flag to reset Timer
	if (resetToDefaults) 
		ResetToDefaults();

	if (active && ticks == -1) // infinity case
	{
		CheckTime(period, timeStep);
	}
	else if (active && ticks >= 1) // countdown timer case
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

// Собирает дефолтные значения на первом апдейте
void TimerFlowNode::CollectDefaults()
{
	timerDefaults.active_ = inputs_[Active]->ReadData().GetBool();
	timerDefaults.preriod_ = inputs_[Period]->ReadData().GetFloat();
	timerDefaults.maxticks_ = inputs_[MaxTicks]->ReadData().GetInt();
	
	defaultsCollected_ = true;
}

// Ресает все важные порты к дефолтным значениям
void TimerFlowNode::ResetToDefaults()
{
	elapsedTime = 0.0f;
	inputs_[Active]->data_ = timerDefaults.active_;
	inputs_[Period]->data_ = timerDefaults.preriod_;
	inputs_[MaxTicks]->data_ = timerDefaults.maxticks_;

	inputs_[Reset]->data_ = false;
}
