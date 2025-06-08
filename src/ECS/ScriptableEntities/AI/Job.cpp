#include "Job.hpp"
#include "../Buildings/HutBase.hpp"
#include <glm/glm.hpp>  // for glm::distance

Job::Job() : ownerHut(nullptr), state(State::NotStarted), currentWaypoint(0), resourceReward(0) {}

Job::Job(HutBase* owner, const std::vector<glm::vec3>& waypoints, int reward)
    : ownerHut(owner), waypoints(waypoints), resourceReward(reward), state(State::NotStarted), currentWaypoint(0) {}

void Job::AllocateResources() {
    if (ownerHut) {
        ownerHut->AllocateResource();
    }
}

void Job::Update(const glm::vec3& aiPosition) {
    if (state != State::InProgress || waypoints.empty())
        return;

    if (glm::distance(aiPosition, waypoints[currentWaypoint]) < 0.5f) {
        currentWaypoint++;
        if (currentWaypoint >= waypoints.size()) {
            // Add more conditions here if needed before completing the job
            AllocateResources();
            state = State::Completed;
        }
    }
}
