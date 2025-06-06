#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/Transform.hpp>

#include <Canis/Camera.hpp>

class PlayerCamera : public Canis::ScriptableEntity
{
private:
    bool m_mouseLock = false;
    glm::vec2 m_mousePosBeforeLock;
public:
    Canis::Entity target;
    Canis::Entity cameraPivot;
    float mouseSensitivity = 0.4f;
    float rotationSpeed = 45.0f;
    float maxZoom = 1.0f;
    float minZoom = 0.3f;
    float zoomSpeed = 2.0f;

    void OnCreate() {}

    void OnReady() {
        target = entity.GetEntityWithTag("PLAYER");
        if (!target)
            Canis::FatalError("PlayerCamera could not find tag PLAYER");
        
        if (!(cameraPivot = entity.GetEntityWithTag("CAMERAPIVOT")))
            Canis::FatalError("PlayerCamera could not find tag CAMERAPIVOT");

        entity.SetParent(cameraPivot);
    }

    void OnDestroy() {}

    void OnUpdate(float _dt)
    {
        if (GetScene().timeScale == 0.0f)
            return;
        
        using namespace Canis;
        using namespace glm;

        bool lastMouseLock = m_mouseLock;

        m_mouseLock = (GetInputManager().GetRightClick() ||
                        GetInputManager().GetKey(SDL_SCANCODE_LCTRL) ||
                        GetInputManager().GetKey(SDL_SCANCODE_RCTRL));
        
        GetWindow().MouseLock(m_mouseLock);

        if (m_mouseLock == false && lastMouseLock == true)
            GetWindow().SetMousePosition(m_mousePosBeforeLock.x, m_mousePosBeforeLock.y);
        
        if (m_mouseLock == true && lastMouseLock == false)
            m_mousePosBeforeLock = GetInputManager().mouse;
        
        Transform& targetTransform = target.GetComponent<Transform>();
        Transform& transform = GetComponent<Transform>();

        Entity parent = Entity(transform.parent, entity.scene);
        Transform& parentTransform = parent.GetComponent<Transform>();
        
        Camera& camera = GetCamera();

        SetTransformPosition(parentTransform, GetGlobalPosition(targetTransform));

        float inputX = -GetInputManager().mouseRel.x;

        if (inputX == 0.0f)
        {
            if (GetInputManager().GetKey(SDL_SCANCODE_LEFT))
                inputX = -1;
            else if (GetInputManager().GetKey(SDL_SCANCODE_RIGHT))
                inputX = 1;
        }

        if (m_mouseLock == true) // mouse look
            Canis::Rotate(parentTransform, vec3(0.0f, radians(inputX * mouseSensitivity * rotationSpeed * _dt), 0.0f));
        else if (m_mouseLock == false && GetInputManager().GetRightStick().x != 0.0f) // controller look
            Canis::Rotate(parentTransform, vec3(0.0f, radians(GetInputManager().GetRightStick().x * rotationSpeed * _dt), 0.0f));
        else if (GetInputManager().GetKey(SDL_SCANCODE_LEFT) || GetInputManager().GetKey(SDL_SCANCODE_RIGHT)) // keyboard input
            Canis::Rotate(parentTransform, vec3(0.0f, radians(inputX * rotationSpeed * _dt), 0.0f));
        
        if (inputX != 0.0f)
        {
            //Canis::Log("Camera: " + glm::to_string(GetGlobalPosition(transform)));
        }

        // zoom
        float dist = glm::distance(target.GetGlobalPosition(), entity.GetGlobalPosition());
        if (parentTransform.scale.x > minZoom)
        {
            if (GetInputManager().GetKey(SDL_SCANCODE_I) ||
                GetInputManager().VerticalScroll() > 0)
            {
                SetTransformScale(parentTransform, vec3(parentTransform.scale.x - (zoomSpeed * _dt)));
            }
        }

        if (parentTransform.scale.x < maxZoom)
        {
            if (GetInputManager().GetKey(SDL_SCANCODE_O) ||
                GetInputManager().VerticalScroll() < 0)
            {
                SetTransformScale(parentTransform, vec3(parentTransform.scale.x + (zoomSpeed * _dt)));
            }
        }

        camera.Position = GetGlobalPosition(transform);
        camera.Front = normalize(GetGlobalPosition(targetTransform) - camera.Position);


    }
};

