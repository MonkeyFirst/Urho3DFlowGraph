#include "CustomFlowNode.h"

CustomFlowNodeComponent::CustomFlowNodeComponent(Context * context) : 
	Component(context),
	flowNode_(nullptr)
{
	creationParams_.flowNodeName = "CustomFlowNodeComponent";
}

CustomFlowNodeComponent::~CustomFlowNodeComponent()
{
}

void CustomFlowNodeComponent::RegisterObject(Context* context)
{
	context->RegisterFactory<CustomFlowNodeComponent>();
}

FlowNodeCreationParams& CustomFlowNodeComponent::GetFlowNodeCreationParams()
{
	return creationParams_;
}

SharedPtr<FlowNode> CustomFlowNodeComponent::GetFlowNode()
{
	return flowNode_;
}

void CustomFlowNodeComponent::UpdateCustomFlowNode(FlowNode* flowNode)
{
	
}
