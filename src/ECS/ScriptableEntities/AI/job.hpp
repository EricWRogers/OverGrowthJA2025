#pragma once
#include <vector>
#include <glm/vec3.hpp>

class Job {
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
    Job() : waypoints(), resourceReward(0) {}
    Job(const std::vector<glm::vec3>& _waypoints, int reward)
        : waypoints(_waypoints), resourceReward(reward) {

        }

    State GetState() const { return state; }

    void Start() { 
        state = State::InProgress; 
    }

    void Update(const glm::vec3& aiPosition) { 
        if (state != State::InProgress || waypoints.empty())
            return;

        if (glm::distance(aiPosition, waypoints[currentWaypoint]) < 0.5f) {
            currentWaypoint++;
            if (currentWaypoint >= waypoints.size()) {//Essentially we need to add here more conditions before we complete the job. Like a timer or something idk. Wait for an aimation to play. WHo knows.
                state = State::Completed;
                AllocateResources();
                state = State::Completed;
            }
        }
    }

    void AllocateResources() { //We sorta need a resource manager for me to increment.
        
    }

    bool IsCompleted() const { 
        return state == State::Completed; 
    }
    const std::vector<glm::vec3>& GetWaypoints() const { 
        return waypoints; 
    }
};


//For u aiden <3
// if (job.GetState() == Job::State::InProgress) {
//     job.Update(aiEntity.GetPosition());
//     if (job.IsCompleted()) {
//         //Job is done
//     }
// }
