#ifndef ENGINE_H
#define ENGINE_H

#include "EngineCore.h"

#include "ArchetypeManager.h"
#include "EntityManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "OverlaySystem.h"
#include "PrefabLoader.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "WindowManager.h"

class Engine {
   public:
    Engine();
    ~Engine();

    void initialize();  // Setup all systems and managers
    void engage();      // Start the main loop
    void shutdown();    // Clean up all resources

   private:
    void create();        // test Create
    void run();           // Main loop
    void mark();          // Mark frame
    void processInput();  // Handle input
    void update();        // Call system updates
    void render();        // Main Rendering
    void log();           // System Logging - RR
    void display();       // Display function - RR

    // Managers
    std::unique_ptr<WindowManager> windowManager;
    std::unique_ptr<PrefabLoader> prefabLoader;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<ArchetypeManager> archetypeManager;
    std::unique_ptr<ShaderManager> shaderManager;
    std::unique_ptr<MeshManager> meshManager;
    std::unique_ptr<TextureManager> textureManager;
    std::unique_ptr<MaterialManager> materialManager;

    // Systems
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<RenderSystem> renderSystem;
    std::unique_ptr<OverlaySystem> overlaySystem;

    // Global
    TimeManager& timeManager;

    bool running;
};

#endif
