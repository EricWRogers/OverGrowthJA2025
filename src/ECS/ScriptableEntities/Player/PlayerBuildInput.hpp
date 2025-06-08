#pragma once
#include <string>
#include <vector>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/ECS/Components/Mesh.hpp>
#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>

#include <Canis/Camera.hpp>
#include <Canis/DataStructure/List.hpp>
#include <Canis/GameHelper/AStar.hpp>
#include "../Characters/WavePointsManager.hpp"
#include <Canis/Entity.hpp>

using namespace Canis;

class PlayerBuildInput : public Canis::ScriptableEntity
{
    private:
        Transform visTransform;
        Entity visEntity;
        WavePointsManager wpm;
        std::string buildingPrefabs[6] = { 
            "",
            "",
            "",
            "",
            "",
            ""
        };
    public:
        enum BuildingType {
            Barracks,
            Farm,
            Hut,
            Sapling,
            TownHall,
            WoodHut
        };
        enum BuildingType currentType = WoodHut;
        void OnCreate(){
            wpm = entity.GetEntityWithTag("GRIDLAYOUT").GetScript<WavePointsManager>();
            Canis::Log("Create");
            //create visual object
            visEntity = CreateEntity();
            visTransform = visEntity.AddComponent<Transform>();
            visEntity.SetPosition(vec3(0,0,0));
            visEntity.SetScale(vec3(.9f, .1f, .9f));
            visEntity.AddComponent<SphereCollider>();
            visEntity.AddComponent<Color>();
            Mesh& mesh = visEntity.AddComponent<Mesh>();
            mesh.modelHandle.id = AssetManager::LoadModel("assets/models/white_block.obj");
            mesh.material = AssetManager::LoadMaterial("assets/materials/default.material");
            visTransform.active = false;
        };

        void OnUpdate(float _dt)
        {
            if (GetScene().timeScale == 0.0f) return;
            vec2 v = GetInputManager().mouse;
            Canis::Camera c = GetCamera();
            Canis::Ray ray = Canis::RayFromScreen(c, GetWindow(), v);
            if (ray.direction.y == 0) { //avoid div by zero, ray is parallel to the ground
                visTransform.active = false;
                return;
            } 
            float t = -(ray.origin.y/ray.direction.y); //supposed to be doing some dot products but they're all up (0,1,0) so just use y
            vec3 point = ray.origin + t * ray.direction;
            point += vec3(std::signbit(point.x) ? -.5f : .5f, 0, std::signbit(point.z) ? -.5f : .5f); //offset point, needs to be reversed for negative points
            point = vec3(point.x - fmod(point.x, 1), 0, point.z - fmod(point.z, 1)); //remove decimal
            visTransform.active = true;
            visEntity.SetPosition(point);
            if (GetInputManager().JustLeftClicked()) {
                Canis::Log("Trying to place building "+std::to_string(currentType));    
                unsigned int wpmPoint = wpm.aStar.GetPointByPosition(point);
                if (wpmPoint == 0) {
                    Canis::Log("Not able to place at "+std::to_string(point.x)+","+std::to_string(point.z));
                    return;
                } 
                Entity newBuild = CreateEntity();
                newBuild.AddComponent<Transform>();
                newBuild.SetPosition(point + vec3(0,.5f,0));
                newBuild.SetScale(vec3(.9f, 1.0f, .9f));
                newBuild.AddComponent<SphereCollider>();
                newBuild.AddComponent<Color>();
                Mesh& mesh = newBuild.AddComponent<Mesh>();
                mesh.modelHandle.id = AssetManager::LoadModel("assets/models/white_block.obj");
                mesh.material = AssetManager::LoadMaterial("assets/materials/default.material");
                wpm.aStar.RemovePoint(wpm.aStar.GetClosestPoint(point));
            }
        };
};