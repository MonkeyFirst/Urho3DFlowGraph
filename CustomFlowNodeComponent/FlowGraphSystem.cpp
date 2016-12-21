#include "FlowGraphSystem.h"

#include "FlowGraph.h"
#include "FlowNode.h"
#include "CustomFlowNode.h"


FlowGraphSystem::FlowGraphSystem(Context * context) : Object(context)
{
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(FlowGraphSystem, HandleUpdate));
	SubscribeToEvent(E_COMPONENTADDED, URHO3D_HANDLER(FlowGraphSystem, HandleComponentAdded));

}

FlowGraphSystem::~FlowGraphSystem()
{
	UnsubscribeFromAllEvents();
}

void FlowGraphSystem::PushUpdateFlowGraph(SharedPtr<FlowGraph> newFG)
{
	flowGraphs_.Push(newFG);
}

void FlowGraphSystem::HandleUpdate(StringHash eventType, VariantMap & eventData)
{
	URHO3D_PROFILE(FlowGraphUpdate);

	using namespace Update;
	float timeStep = eventData[P_TIMESTEP].GetFloat();

	for (unsigned int i = 0; i < flowGraphs_.Size(); i++) 
	{
		FlowGraph* fg = flowGraphs_[i].Get();
		if (fg != nullptr)
			if (fg->isActive_)
			{
				String name = fg->GetName();
				fg->Update(timeStep);
			}
	}
}

// Следит за добавление всех компонентов которые унаследованы от CustomFlowNodeComponent
// Если находит создает такому компоненту обычную FlowNode
void FlowGraphSystem::HandleComponentAdded(StringHash eventType, VariantMap& eventData)
{
	using namespace ComponentAdded;
	Component* component = (Component*)(eventData[P_COMPONENT].GetPtr());
	if (component != nullptr)
		
		if (component->IsInstanceOf<CustomFlowNodeComponent>())
		{
			CustomFlowNodeComponent* cfn = (CustomFlowNodeComponent*)component;

			FlowNodeCreationParams& params = cfn->GetFlowNodeCreationParams();

			// нода по описанию портов
			cfn->flowNode_ = CreateFlowNodeFromParams(params);
			// указатель на флауноду для компонента 
			cfn->flowNode_->customFlowNode_ = cfn;
			// имя для индикации в графедиторе
			cfn->flowNode_->name_ = params.flowNodeName;
		}
}

// Хелпер, создает из параметров описания - флоуноду
SharedPtr<FlowNode> FlowGraphSystem::CreateFlowNodeFromParams(FlowNodeCreationParams& params)
{
	SharedPtr<FlowNode> flownode_(new FlowNode(context_));


	flownode_->inputs_.Resize(params.inputPortsName.Size());
	flownode_->outputs_.Resize(params.outputPortsName.Size());

	// Создаем входные порты.
	for (unsigned int i = 0; i < params.inputPortsName.Size(); ++i)
	{
		SharedPtr<FlowInputPort> inputPort(new FlowInputPort(context_));
		inputPort->node_ = flownode_;					// port's owner
		inputPort->data_ = params.inputPortsVal[i];		// default value
		inputPort->name_ = params.inputPortsName[i];	// node's port name

		flownode_->inputs_[i] = inputPort;
	}

	// Создаем выходные порты.
	for (unsigned int i = 0; i < params.outputPortsName.Size(); ++i)
	{
		SharedPtr<FlowInputPort> outputPort(new FlowInputPort(context_));
		outputPort->node_ = flownode_;					// port's owner
		outputPort->data_ = params.inputPortsVal[i];		// default value
		outputPort->name_ = params.inputPortsName[i];	// node's port name

		flownode_->outputs_[i] = outputPort;
	}

	return flownode_;
}