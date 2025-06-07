#pragma once

struct NPCBoid
{
    glm::vec3 target;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float drag = 0.95f;
    float speed = 0.0f;
    float maxSpeed = 3.0f;
};