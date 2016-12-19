#include <Urho3D/Urho3DAll.h>
#include "FlowGraph.h"
#include "CameraControllerFlowNode.h"
#include "CubeCreatorFlowNode.h"
#include "StarterFlowNode.h"

class Game : public Application
{
    URHO3D_OBJECT(Game, Application);

public:
    SharedPtr<Scene> scene_;
    WeakPtr<Node> cameraNode_;
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;

    SharedPtr<FlowGraph> flowGraphExample_;

    Game(Context* context) : Application(context)
    {
    }

    void Setup()
    {
        engineParameters_[EP_FULL_SCREEN] = false;
        engineParameters_[EP_WINDOW_RESIZABLE] = true;
    }

    void Start()
    {
        CreateScene();
        SetupViewport();
        SubscribeToEvents();

        CreateFlowGraph();
    }

    void SetupViewport()
    {
        SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
        GetSubsystem<Renderer>()->SetViewport(0, viewport);
    }

    void CreateScene()
    {
        scene_ = new Scene(context_);
        scene_->CreateComponent<Octree>();

        ResourceCache* cache = GetSubsystem<ResourceCache>();

        Node* planeNode = scene_->CreateChild("Plane");
        planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
        StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
        planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
        planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

        Node* lightNode = scene_->CreateChild("DirectionalLight");
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
        cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
    }

    void SubscribeToEvents()
    {
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Game, HandleUpdate));
    }

    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        using namespace Update;
        float timeStep = eventData[P_TIMESTEP].GetFloat();

    }

    void CreateFlowGraph()
    {
        // Создаем граф. Граф управляет очередностью выполнения кода в флаунодах.
        flowGraphExample_ = new FlowGraph(context_);

        // Пример флауноды, которая управляет камерой.
        SharedPtr<CameraControllerFlowNode> cameraController(new CameraControllerFlowNode(context_));
        // Записываем данные в входные порты. Пользователь может это делать в редакторе.
        // Сами порты уже созданы в конструкторе CameraControllerFlowNode.
        cameraController->inputs_[CameraControllerFlowNode::IN_CAMERA_NODE]->data_ = (void*)scene_->GetChild("Camera");
        cameraController->inputs_[CameraControllerFlowNode::IN_MOUSE_SENSITIVITY]->data_ = 0.1f;
        // Добавляем эту флауноду в граф.
        flowGraphExample_->nodes_.Push(cameraController);

        // Пример цепочки нод. Первая флоунода отправляет сигнал при запуске (первом апдейте), а вторая создает куб при входящем сигнале.
        
        SharedPtr<StarterFlowNode> starter(new StarterFlowNode(context_));
        flowGraphExample_->nodes_.Push(starter);

        SharedPtr<CubeCreatorFlowNode> cubeCreator(new CubeCreatorFlowNode(context_));
        //cubeCreator->inputs_["Create!"]->data_ = true;
        cubeCreator->inputs_[CubeCreatorFlowNode::IN_SCENE]->data_ = (void*)scene_;
        flowGraphExample_->nodes_.Push(cubeCreator);

        // Присоединяем криэйтор к стартеру.
        flowGraphExample_->Connect(starter->outputs_[StarterFlowNode::OUT_START_SIGNAL],
            cubeCreator->inputs_[CubeCreatorFlowNode::IN_CREATE_SIGNAL]);
    }

};

URHO3D_DEFINE_APPLICATION_MAIN(Game)
