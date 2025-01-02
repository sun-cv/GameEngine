
#include "EntityBuilder.h"

#include "CoreComponent.h"


namespace ECS
{
EntityBuilder::EntityBuilder(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager) : entityManager(entityManager), meshManager(meshManager), materialManager(materialManager)
{
}

EntityBuilder::~EntityBuilder()
{
}

EntityBuilder& EntityBuilder::create(std::string tag)
{
    entity = entityManager->createEntity(tag);
    return *this;
}

EntityBuilder& EntityBuilder::enemy(bool value = true)
{
    if (entity)
    {
        auto& enemy = entity->add<Enemy>();
        enemy.state = value;
    }
    return *this;
}

EntityBuilder& EntityBuilder::player(bool value = true)
{
    if (entity)
    {
        auto& player = entity->add<Player>();
        player.state = value;
    }
    return *this;
}
EntityBuilder& EntityBuilder::lifespan(size value)
{
    if (entity)
    {
        auto& lifespan = entity->add<Lifespan>();
        lifespan.age = value;
    }
    return *this;
}

EntityBuilder& EntityBuilder::position(Vector2 vector)
{
    if (entity)
    {
        auto& position = entity->add<Position>();
        position.x = vector.x;
        position.y = vector.y;
    }
    return *this;
}

EntityBuilder& EntityBuilder::render(std::string mesh, std::string material)
{
    if (entity)
    { 
        auto& render = entity->add<Render>();
        render.mesh = meshManager->getMesh(mesh);

        auto& vertices = render.mesh->getVertices();

            for (size_t i = 0; i < vertices.size(); i += 4) {
        std::cout << "(" << vertices[i] << ", " << vertices[i + 1] << ")" << std::endl;
    }
        render.material = materialManager->getMaterial(material);
    }
    return *this;
}

EntityBuilder& EntityBuilder::title(std::string name)
{
    if (entity)
    {
        auto& title = entity->add<Title>();
        title.name = name;
    }
    return *this;
}

EntityBuilder & EntityBuilder::velocity(Vector2 vector)
{
    if (entity)
    {
        auto& velocity = entity->add<Velocity>();
        velocity.x = vector.x;
        velocity.y = vector.y;

    }
    return *this;
}

Entity EntityBuilder::complete()
{
    if (!entity)
    {
        Log_(Log::Error, Log::bEntity, "Failed entity creation");
    }
    return entity.value();
}
}