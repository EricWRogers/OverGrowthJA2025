#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

#include "../AI/Job.hpp"

class HutBase : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = true;
    
public:
    float counter = 0;
    float max_health = 100;
    float current_health = 0;
    float create_resource_interval = 60; //Seconds
   
    Job job;

     HutBase() : job() {}

    void OnCreate();
    
    void OnReady();

    void OnDestroy();

    void OnUpdate(float _dt);

    virtual void AllocateResource();
};