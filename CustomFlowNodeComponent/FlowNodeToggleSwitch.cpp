#include "FlowNodeToggleSwitch.h"

ToggleSwitchFlowNode::ToggleSwitchFlowNode(Context * context) :
	FlowNode(context),
	flag_(false)
{
	name_ = "ToggleSwitchFlowNode";

	inputs_.Resize(InputLast);
	outputs_.Resize(OutputLast);

	// Создаем входные порты.
	SharedPtr<FlowInputPort> toggle(new FlowInputPort(context));
	toggle->node_ = this;
	toggle->data_ = Variant(false); // default value
	inputs_[Toggle] = toggle;

	SharedPtr<FlowOutputPort> turnOn(new FlowOutputPort(context));
	turnOn->node_ = this;
	turnOn->data_ = Variant(true);
	outputs_[TurnOn] = turnOn;

	SharedPtr<FlowOutputPort> turnOff(new FlowOutputPort(context));
	turnOff->data_ = Variant(false);
	turnOff->node_ = this;
	
	outputs_[TurnOff] = turnOff;
	
}

void ToggleSwitchFlowNode::Update(float timeStep)
{
	bool toggle = inputs_[Toggle]->ReadData().GetBool();

	if (toggle) 
	{
		flag_ = !flag_;
	}

	if (flag_)
	{
		outputs_[TurnOn]->data_ = true;
		outputs_[TurnOff]->data_ = false;
	}
	else
	{
		outputs_[TurnOn]->data_ = false;
		outputs_[TurnOff]->data_ = true;
	}
}
