#include "AiBrain.hpp"
#include <algorithm>

void AiBrain::OnCreate()
{
    Canis::Log("Brain is braining");
}

void AiBrain::OnReady()
{
    //Not needed rn
}

void AiBrain::OnUpdate(float _dt)
{
    // counter -= _dt;

    // if (counter < 0.0f) {
       
    //     counter = 1.0f;
    // }
}

void AiBrain::RegisterAI(NPC* unit) {
    aiUnits.push_back(unit);
}

void AiBrain::UnregisterAI(NPC* unit) {
    aiUnits.erase(std::remove(aiUnits.begin(), aiUnits.end(), unit), aiUnits.end());
}

void AiBrain::RegisterBuilding(HutBase* building) {
    buildings.push_back(building);
}

void AiBrain::UnregisterBuilding(HutBase* building) {
    buildings.erase(std::remove(buildings.begin(), buildings.end(), building), buildings.end());
}

void AiBrain::AddJob(const Job& job) {
    jobQueue.push(job);
}

bool AiBrain::HasJobs() const {
    return !jobQueue.empty();
}

Job AiBrain::RequestJob() {
    if (jobQueue.empty()) {
        return Job{};
    }
    Job job = jobQueue.front();
    jobQueue.pop();
    return job;
}

bool AiBrain::RequestJob(NPC* npc, Job& outJob) {
    if (jobQueue.empty()) return false;
    outJob = jobQueue.front();
    jobQueue.pop();
    return true;
}

void AiBrain::CompleteJob(const Job& job) {
    // optionally: log, recycle, or archive the job
}
