#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

#include "../AI/Job.hpp"


class AiBrain;

class HutBase : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = true;
    AiBrain* aiBrain = nullptr;
    
public:
    float counter = 0;
    float max_health = 100;
    float current_health = 0;
    float job_creation_interval = 60; //Seconds
    float create_resource_interval = 60.0f;

    std::vector<glm::vec3> jobPositions;  
    int jobPriority = 0; 

    Job job;

     HutBase() : job(this, {}, 0) {}

    void OnCreate();
    
    void OnReady();

    void OnDestroy();

    void OnUpdate(float _dt);

    virtual void AllocateResource();
};