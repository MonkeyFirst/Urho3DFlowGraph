Scene@ scene_;

void Start()
{
    scene_ = Scene();

    scene_.CreateComponent("Octree");
    Node@ cameraNode = scene_.CreateChild("MyCamera");
    cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(0.0f, 0.0f, -5.0f);
    
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;

    Node@ boxNode = scene_.CreateChild("MyBox");
    StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
    boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
    boxNode.rotation = Quaternion(45.0f, 45.0f, 45.0f);

    Node@ lightNode = scene_.CreateChild("MyLight");
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    lightNode.direction = Vector3(0.6f, -0.6f, 0.8f);


    SubscribeToEvent("Update", "HandleUpdate");
    
    int x = VAR_ANY;
    
    FlowOutputPort@ port = FlowOutputPort();
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    
    Node@ boxNode = scene_.GetChild("MyBox");
    boxNode.Rotate(Quaternion(10.0f * timeStep, 10.0f * timeStep, 10.0f * timeStep));
}
