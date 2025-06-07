#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include <Canis/ECS/Systems/System.hpp>

#include "../Components/Billboard.hpp"

class BillboardSystem : public Canis::System
{
private:
public:
    BillboardSystem() : Canis::System() { m_name = type_name<BillboardSystem>(); }

    void Create() {}
    void Ready() {}

    void Update(entt::registry &_registry, float _deltaTime) 
    {
        auto view = _registry.view<Canis::Transform, Billboard>();

        for (auto [id, transform, billboard] : view.each())
        {
            Canis::Entity entity(id, scene);

            Canis::LookAt(transform, scene->camera->Position, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
};

static bool DecodeBillboardSystem(const std::string &_name, Canis::Scene *_scene)
{
    if (_name == "BillboardSystem")
    {
        _scene->CreateSystem<BillboardSystem>();
        return true;
    }
    return false;
}