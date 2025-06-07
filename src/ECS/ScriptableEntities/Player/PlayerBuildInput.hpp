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

using namespace Canis;

class Coords {
    public:
        int x;
        int y;

        Coords(int _x, int _y) {
            x = _x;
            y = _y;
        };
};

class PlayerBuildInput : public Canis::ScriptableEntity
{
    private:
        std::vector<Coords> buildingsPlaced;
    public:
        void OnUpdate(float _dt)
        {
            if (GetScene().timeScale == 0.0f) return;
            vec2 v = GetInputManager().mouse;
            Canis::Camera c = GetCamera();
            Canis::Ray ray = Canis::RayFromScreen(c, GetWindow(), v);
            if (ray.direction.y == 0) return; //avoid div by zero, ray is parallel to the ground
            float t = -(ray.origin.y/ray.direction.y); //supposed to be doing some dot products but they're all up (0,1,0) so just use y
            vec3 point = ray.origin + t * ray.direction;
            point = vec3(point.x - fmod(point.x, 1), 0, point.z - fmod(point.z, 1));
            //Canis::Log(std::to_string(point.x)+","+std::to_string(point.y)+","+std::to_string(point.z));
            if (GetInputManager().JustLeftClicked()) {
                Canis::Log("Trying to place building");
                for (int i = 0; i < buildingsPlaced.size(); i++) {
                    if (buildingsPlaced[i].x == (int)point.x && buildingsPlaced[i].y == (int)point.z) {
                        Canis::Log("Building detected");
                        return;
                    }
                }
                Entity newBuild = CreateEntity();
                newBuild.AddComponent<Transform>();
                newBuild.SetPosition(point);
                newBuild.SetScale(vec3(.9f, 1.0f, .9f));
                newBuild.AddComponent<SphereCollider>();
                newBuild.AddComponent<Color>();
                Mesh& mesh = newBuild.AddComponent<Mesh>();
                mesh.modelHandle.id = AssetManager::LoadModel("assets/models/white_block.obj");
                mesh.material = AssetManager::LoadMaterial("assets/materials/default.material");
                Canis::Log(std::to_string(newBuild.GetGlobalPosition().x));
                buildingsPlaced.push_back(Coords((int)point.x,(int)point.z));
            }
        };
};