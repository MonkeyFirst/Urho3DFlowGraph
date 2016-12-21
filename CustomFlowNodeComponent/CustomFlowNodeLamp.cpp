#include "CustomFlowNodeLamp.h"

CustomFlowNodeLamp::CustomFlowNodeLamp(Context * context) : CustomFlowNodeComponent(context)
{
	creationParams_.flowNodeName = "MyLampFlowNodeExposedIntoFG";
	creationParams_.AddInputPort("Enable", Variant(true));
	creationParams_.AddInputPort("LightColor", Variant(Vector3(1.0f,1.0f,1.0f)));
	creationParams_.AddOutputPort("Changed", Variant(true));
}

CustomFlowNodeLamp::~CustomFlowNodeLamp()
{

}

void CustomFlowNodeLamp::RegisterObject(Context * context)
{
	context->RegisterFactory<CustomFlowNodeLamp>();
}

void CustomFlowNodeLamp::UpdateCustomFlowNode(FlowNode * flowNode) 
{
	static bool en = false;
	static Vector3 c = Vector3::ONE;

	bool enable = flowNode->inputs_[Enable]->ReadData().GetBool();
	Vector3 color = flowNode->inputs_[LightColor]->ReadData().GetVector3();

	// Если что-то изменилось у лампочки - пошлём оповещение на выход
	if (en != enable || ((c - color).Length() > 0.1f))
		flowNode->outputs_[Changed]->data_ = true;
	else
		flowNode->outputs_[Changed]->data_ = false;


	// реакция на изменения на входящих портах
	GetNode()->GetComponent<Light>()->SetEnabled(enable);


	// Update info
	en = enable;
	c = color;
}
