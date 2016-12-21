Scene@ scene_;

void Start()
{
    scene_ = Scene();
    scene_.CreateComponent("Octree");

    Node@ planeNode = scene_.CreateChild("Plane");
    planeNode.scale = Vector3(100.0f, 1.0f, 100.0f);
    StaticModel@ planeObject = planeNode.CreateComponent("StaticModel");
    planeObject.model = cache.GetResource("Model", "Models/Plane.mdl");
    planeObject.material = cache.GetResource("Model", "Materials/StoneTiled.xml");

/*        Node* lightNode = scene_->CreateChild("DirectionalLight");
        lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
        Light* light = lightNode->CreateComponent<Light>();
        light->SetColor(Color(0.5f, 0.5f, 0.5f));
        light->SetLightType(LIGHT_DIRECTIONAL);
        light->SetCastShadows(true);
        light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
        light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
        //light->SetShadowIntensity(0.5f);

        Node* zoneNode = scene_->CreateChild("Zone");
        Zone* zone = zoneNode->CreateComponent<Zone>();
        zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
        zone->SetAmbientColor(Color(0.5f, 0.5f, 0.5f));
        zone->SetFogColor(Color(0.4f, 0.5f, 0.8f));
        zone->SetFogStart(100.0f);
        zone->SetFogEnd(300.0f);

        const unsigned NUM_OBJECTS = 200;
        for (unsigned i = 0; i < NUM_OBJECTS; ++i)
        {
            Node* mushroomNode = scene_->CreateChild("Mushroom");
            mushroomNode->SetPosition(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));
            mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
            mushroomNode->SetScale(0.5f + Random(2.0f));
            StaticModel* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
            mushroomObject->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
            mushroomObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
            mushroomObject->SetCastShadows(true);
        }

        cameraNode_ = scene_->CreateChild("Camera");
        cameraNode_->CreateComponent<Camera>();
        cameraNode_->SetPosition(Vector3(0.0f, 5.0f, -7.0f));



*/










    Node@ cameraNode = scene_.CreateChild("MyCamera");
    cameraNode.CreateComponent("Camera");
    cameraNode.position = Vector3(0.0f, 5.0f, -5.0f);
    
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
    
    //int x = VAR_ANY;
    //FlowOutputPort@ port = FlowOutputPort();
    //port.name_ = "Blablabla";
    
    CreateFlowGraph();
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    
    Node@ boxNode = scene_.GetChild("MyBox");
    boxNode.Rotate(Quaternion(10.0f * timeStep, 10.0f * timeStep, 10.0f * timeStep));
}

FlowGraph@ flowGraphExample;
CameraControllerFlowNode@ cameraController;

void CreateFlowGraph()
{
    // Создаем граф. Граф управляет очередностью выполнения кода в флаунодах.
    flowGraphExample = FlowGraph();

    // Пример флауноды, которая управляет камерой.
    cameraController = CameraControllerFlowNode();
    cameraController.SetInputPortData(0, Variant(scene_.GetChild("MyCamera")));
    cameraController.SetInputPortData(1, Variant(0.1));
    
    flowGraphExample.AddFlowNode(cameraController);

    /*// Записываем данные в входные порты. Пользователь может это делать в редакторе.
    // Сами порты уже созданы в конструкторе CameraControllerFlowNode.
    //cameraController->inputs_[CameraControllerFlowNode::IN_CAMERA_NODE]->data_ = (void*)scene_->GetChild("Camera");
    cameraController->inputs_[CameraControllerFlowNode::IN_MOUSE_SENSITIVITY]->data_ = 0.1f;
    
    // Добавляем эту флауноду в граф.
    flowGraphExample_->nodes_.Push(cameraController);

    // Пример цепочки нод. Первая флоунода отправляет сигнал при запуске (первом апдейте), а вторая создает куб при входящем сигнале.
      
    SharedPtr<StarterFlowNode> starter(new StarterFlowNode(context_));
    flowGraphExample_->nodes_.Push(starter);

    SharedPtr<CubeCreatorFlowNode> cubeCreator(new CubeCreatorFlowNode(context_));
    //cubeCreator->inputs_[CubeCreatorFlowNode::IN_CREATE_SIGNAL]->data_ = true;
    cubeCreator->inputs_[CubeCreatorFlowNode::IN_SCENE]->data_ = (void*)scene_;
    flowGraphExample_->nodes_.Push(cubeCreator);

    // Присоединяем криэйтор к стартеру.
    flowGraphExample_->Connect(starter->outputs_[StarterFlowNode::OUT_START_SIGNAL],
    cubeCreator->inputs_[CubeCreatorFlowNode::IN_CREATE_SIGNAL]);
*/
}
