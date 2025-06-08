#pragma once
#include <vector>
#include <glm/vec3.hpp>

class HutBase;

class Job {
    HutBase* ownerHut = nullptr;

public:
    enum class State {
        NotStarted,
        InProgress,
        AtWaypoint,
        Completed,
        Failed
    };

private:
    State state = State::NotStarted;
    std::vector<glm::vec3> waypoints;
    size_t currentWaypoint = 0;
    int resourceReward = 0;

public:
    Job();
    Job(HutBase* owner, const std::vector<glm::vec3>& waypoints, int reward);

    void AllocateResources();  // Only declaration here

    State GetState() const { return state; }
    void Start() { state = State::InProgress; }

    void Update(const glm::vec3& aiPosition);

    bool IsCompleted() const { return state == State::Completed; }
    const std::vector<glm::vec3>& GetWaypoints() const { return waypoints; }
};
