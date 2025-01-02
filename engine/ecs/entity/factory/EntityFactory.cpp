#include "EntityFactory.h"

#include "EntityBuilder.h"

namespace ECS
{
EntityFactory::EntityFactory(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager) : entityManager(entityManager), meshManager(meshManager), materialManager(materialManager)
{
}

EntityFactory::~EntityFactory()
{
}

// Entity& EntityFactory::createEntity(std::string tag)
// {
//     return;
// }
}