#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <glm/gtx/rotate_vector.hpp>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/UISliderComponent.hpp>
#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/SceneManager.hpp>

#include <Canis/ECS/Components/Mesh.hpp>
#include <Canis/ECS/Systems/RenderMeshSystem.hpp>

class PlayerMovement : public Canis::ScriptableEntity
{
public:
    Canis::Entity camera;

    float speed = 10.0f;
    float gravity = -25.0f;
    float jumpForce = 15.0f;
    float groundLevel = 0.0f;
    float yOffset = 0.5f;
    float turnSpeed = 5.0f;

    bool isGrounded = true;
    bool isWalking = false;

    vec3 acceleration = vec3(0.0f);

    Canis::Entity shadowCamera;
    vec3 shadowCameraOffset = vec3(0.0f); 

    void OnCreate() {
        if (auto *renderer = GetSystem<Canis::RenderMeshSystem>())
        {
            renderer->sortBy = Canis::RenderMeshSystem::SortBy::HEIGHT;
        }

        //std::vector<Canis::Entity> water = GetScene().Instantiate("assets/prefabs/water.prefab");
    }

    void OnReady()
    {
        yOffset = entity.GetComponent<Canis::Transform>().scale.y / 2.0f;
        
        shadowCamera = entity.GetEntityWithTag("DIRECTIONLIGHT");
        shadowCameraOffset = shadowCamera.GetGlobalPosition() - entity.GetGlobalPosition();
    }

    void OnDestroy() {}

    void OnUpdate(float _dt)
    {
        using namespace Canis;
        using namespace glm;

        isWalking = false;
        bool wasGrouded = isGrounded;

        Transform &transform = GetComponent<Transform>();

        vec3 cameraPosition = GetCamera().Position;
        cameraPosition.y = transform.position.y;

        vec3 lookFront = normalize(cameraPosition - transform.position);
        vec3 lookRight = glm::cross(vec3(0.0f, 1.0f, 0.0f), lookFront);

        vec3 targetPosition = transform.position;        

        if (isGrounded == false)
        {
            if (GetInputManager().JustPressedKey(SDLK_BACKSPACE) || 
                GetInputManager().JustPressedKey(SDLK_SPACE) ||
                GetInputManager().JustPressedButton(Canis::ControllerButton::A) ||
                GetInputManager().JustPressedButton(Canis::ControllerButton::RIGHTSHOULDER) ||
                GetInputManager().JustLeftClicked())
                acceleration.y = -jumpForce;
        }

        //if (isGrounded)
        //    acceleration.y = jumpForce;

        //acceleration.y += gravity * _dt;

        //targetPosition.y += acceleration.y * _dt;

        vec2 inputVec = vec2(0.0f);

        inputVec = GetInputManager().GetLeftStick();
        inputVec.y *= -1;

        if (GetInputManager().GetKey(SDL_SCANCODE_W))
            inputVec.y = -1;

        if (GetInputManager().GetKey(SDL_SCANCODE_S))
            inputVec.y = 1;

        if (GetInputManager().GetKey(SDL_SCANCODE_A))
            inputVec.x = -1;

        if (GetInputManager().GetKey(SDL_SCANCODE_D))
            inputVec.x = 1;

        if (inputVec != vec2(0.0f))
        {
            isWalking = true;
            targetPosition += lookFront * (inputVec.y * speed * _dt);
            targetPosition += lookRight * (inputVec.x * speed * _dt);
        }

        if (isWalking)
        {
            bool canReach = false;

            /*if (targetPosition.x < 0 ||
                targetPosition.x > level.map.width ||
                targetPosition.z < 0 ||
                targetPosition.z > level.map.depth)
            return;

            for(int y = 0; y < level.map.height; y++)
            {
                BlockTypes block = (BlockTypes)GetCurrentTileMap(targetPosition.x, y, targetPosition.z);

                if (block == BlockTypes::DIRT || block == BlockTypes::GRASS)
                    canReach = true;
            }*/

            // TODO: REMOVE
            canReach = true;

            if (canReach)
            {
                SetTransformPosition(transform, targetPosition);
            }
        }

        // move shadow
        shadowCamera.SetPosition( entity.GetGlobalPosition() + shadowCameraOffset );
    }
};