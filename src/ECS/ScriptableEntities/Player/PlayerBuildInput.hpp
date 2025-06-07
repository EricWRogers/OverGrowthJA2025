#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/Transform.hpp>

#include <Canis/Camera.hpp>
#include <Canis/Math.hpp>

class PlayerBuildInput : public Canis::ScriptableEntity
{
    public:
        void OnUpdate(float _dt)
        {
            if (GetScene().timeScale == 0.0f) return;
            vec2 v = GetInputManager().mouse;
            Canis::Camera c = GetCamera();
            Canis::Ray ray = Canis::RayFromScreen(c, GetWindow(), v);
            if (ray.direction.y == 0) return; //avoid div by zero
            float t = -(ray.origin.y/ray.direction.y); //supposed to be doing some dot products but they're all up (0,1,0) so just use y
            vec3 point = ray.origin + t * ray.direction;
            Canis::Log(std::to_string(point.x)+","+std::to_string(point.y)+","+std::to_string(point.z));
        };
};