#include "TimerTimer.hpp"

void TimerTimer2D::OnUpdate(float _dt)
{
    counter -= _dt;

    Canis::Log("Logan: " + std::to_string(counter));

    if (counter < 0.0f)
        entity.Destroy();
}