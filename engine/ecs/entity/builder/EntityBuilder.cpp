
#include "EntityBuilder.h"

#include "CoreComponent.h"


namespace ECS
{
EntityBuilder::EntityBuilder(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<ComponentManager> componentManager) : entityManager(entityManager), componentManager(componentManager)
{
    LogSuccess(Log::bEntity);
}

EntityBuilder::~EntityBuilder()
{
    LogPowerDown(Log::bEntity);
}

EntityBuilder& EntityBuilder::create()
{
    entity = entityManager->createEntity();
    return *this;
}

EntityBuilder& EntityBuilder::enemy(bool value = true)
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Enemy>(entity);
    component.state     = value;

    return *this;
}

EntityBuilder& EntityBuilder::player(bool value = true)
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Player>(entity);
    component.state     = value;

    return *this;
}
EntityBuilder& EntityBuilder::lifespan(size value)
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Lifespan>(entity);
    component.age       = value;

    return *this;
}

EntityBuilder& EntityBuilder::position(Vector2 vector)
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component =componentManager->add<Position>(entity);
    component.x         = vector.x;
    component.y         = vector.y;

    return *this;
}

EntityBuilder& EntityBuilder::render(std::string mesh, std::string material, unsigned int layer)
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Render>(entity);
    component.mesh      = mesh;
    component.material  = material;
    component.layer     = layer;
    return *this;

}

EntityBuilder& EntityBuilder::title(std::string name)
{ 
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Title>(entity);
    component.name      = name;

    return *this;
}

EntityBuilder & EntityBuilder::transform()
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Transform>(entity);

    return *this;
}

EntityBuilder & EntityBuilder::velocity(Vector2 vector)
{
    if (entity == INVALID_ENTITY) return *this;

    auto& component     = componentManager->add<Velocity>(entity);
    component.x         = vector.x;
    component.y         = vector.y;

    return *this;
}

    // Returns INVALID_ENTITY if failed.
Entity EntityBuilder::complete()
{
    if (entity == INVALID_ENTITY)
    {
        Log(Log::Error, Log::bEntity, "Failed entity creation");
        return INVALID_ENTITY;
    }
    return entity;
}
}