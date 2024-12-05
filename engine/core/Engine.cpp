#include "Engine.h"

Engine::Engine() : running(false), timeManager(TimeManager::getInstance()) {}

Engine::~Engine() {}

void Engine::initialize() {
    // Window Manager
    windowManager = std::make_unique<WindowManager>();

    if (!windowManager->initialize()) {
        std::cerr << "[FAILED]::[WINDOWMANAGER] Unable to create window instance" << std::endl;
        return;
    }

    // Initialize Managers
    archetypeManager = std::make_unique<ArchetypeManager>();
    entityManager = std::make_unique<EntityManager>(*archetypeManager);
    shaderManager = std::make_unique<ShaderManager>();
    textureManager = std::make_unique<TextureManager>();
    meshManager = std::make_unique<MeshManager>();
    materialManager = std::make_unique<MaterialManager>(*shaderManager, *textureManager);

    // Initialize Renderer
    renderer = std::make_unique<Renderer>();

    // Initialize Systems
    overlaySystem = std::make_unique<OverlaySystem>(*materialManager);
    renderSystem = std::make_unique<RenderSystem>(*renderer, *archetypeManager, *overlaySystem);

    // Initialize PrefabLoader
    prefabLoader = std::make_unique<PrefabLoader>(*entityManager, *meshManager, *materialManager);

    // Load Initial Prefab
    Entity::Handle entity = prefabLoader->createInstance("triangle");
    // Start main loop
    engage();
}

void Engine::engage() {
    std::cout << "[SYSTEM]::[ENGINE] All systems online. Engage!" << std::endl;

    running = true;
    run();
}

void Engine::run() {
    // Create Test
    create();

    while (windowManager->active()) {
        mark();
        processInput();
        update();
        render();
        display();
        log();
    }
}

void Engine::shutdown() {
    std::cout << "[SYSTEM]::[ENGINE] Core systems powering down.." << std::endl;

    running = false;
    windowManager->terminate();
}

void Engine::create() {
    int id = overlaySystem->textSystem.createTextComponent("test", "impactBold", {1, 1}, 1, {1.0, 1.0, 0.5});
    OverlayElement overlayElement;
    overlayElement.addTextComponent(overlaySystem->textSystem.getTextComponent(id));
};

void Engine::mark() { timeManager.update(); }

void Engine::processInput() { windowManager->pollEvents(); }

void Engine::update() {
    // Update logic
}

void Engine::render() { renderSystem->render(); }

void Engine::display() { windowManager->swapBuffers(); }

void Engine::log() {
    // Log loop information
}
