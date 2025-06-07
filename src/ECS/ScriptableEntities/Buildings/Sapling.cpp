#include "Sapling.hpp"

void Sapling::OnCreate() {
    counter = startTime;
}

void Sapling::OnUpdate(float _dt)
{
    counter -= _dt;

    Canis::Log("Logan: " + std::to_string(counter));

    if (counter < 0.0f)
    {
        ChangeModel();
        counter = 10.f;
    }
}

void Sapling::ChangeModel() 
{
    entity.SetScale(glm::vec3(0.20f));
}