#pragma once
#include <Canis/ScriptableEntity.hpp>
#include <vector>
#include <queue>
#include <memory>
#include "Job.hpp"
#include "../Characters/NPC.hpp"
#include "../Buildings/HutBase.hpp"



class AiBrain : public Canis::ScriptableEntity
{
public:
    //And the lists. You shoulden't do operations on these; use the methods.
    std::vector<NPC*> aiUnits;
    std::vector<HutBase*> buildings;

    //JOB QUEUEUEUEU
    std::queue<Job> jobQueue;

    


    //AI can register themselves and unregister. Handy when they spawn and die.
    void RegisterAI(NPC* unit);
    void UnregisterAI(NPC* unit);

    void RegisterBuilding(HutBase* building);
    void UnregisterBuilding(HutBase* building);

    //Job queue stuff
    void AddJob(const Job& job);
    bool HasJobs() const;
    Job RequestJob();

    //Good ol states.
    void OnCreate() override;
    void OnReady() override;
    void OnDestroy() override {}
    void OnUpdate(float _dt) override;

private:
    float counter = 0.0f;
};


