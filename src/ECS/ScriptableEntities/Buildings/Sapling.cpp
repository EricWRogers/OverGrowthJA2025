#include "Sapling.hpp"
using namespace Canis;
void Sapling::OnCreate() {
    counter = startTime;
}

void Sapling::OnUpdate(float _dt)
{
    if (!stop)
    {
        counter -= _dt;

        Canis::Log("Logan: " + std::to_string(counter));

        if (counter < 0.0f)
        {
            if (entity.GetComponent<Transform>().scale.y >= maxSize)
            {
                Canis::Log("Stop");
                counter = 0.0f;
                stop = true;
            } else {
                ChangeModel();
                counter = startTime;
            }
        }
    }
}

void Sapling::ChangeModel() 
{
    entity.SetScale(entity.GetComponent<Transform>().scale + glm::vec3(.20f));
}