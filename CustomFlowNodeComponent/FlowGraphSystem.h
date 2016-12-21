#pragma once
#include <Urho3D/Urho3DAll.h>

class FlowGraph;
class FlowNode;

struct FlowNodeCreationParams;

class URHO3D_API FlowGraphSystem : public Object
{
	URHO3D_OBJECT(FlowGraphSystem, Object);

public:
	FlowGraphSystem(Context* context);
	virtual ~FlowGraphSystem();
	void PushUpdateFlowGraph(SharedPtr<FlowGraph> newFG);

	Vector<SharedPtr<FlowGraph>> flowGraphs_;

protected:
	void HandleUpdate(StringHash eventType, VariantMap& eventData);
	void HandleComponentAdded(StringHash eventType, VariantMap& eventData);
	SharedPtr<FlowNode> CreateFlowNodeFromParams(FlowNodeCreationParams& params);
};