#include <iostream>
#include <algorithm>
#include <vector>

#include "helpers.h"
using namespace std;

//function to get pseudo ranges
std::vector<float> pseudo_range_estimator(std::vector<float> landmark_positions,
                                          float pseudo_position);

//observation model: calculates likelihood prob term based on landmark proximity
float observation_model(std::vector<float> landmark_positions, std::vector<float> observations,
                        std::vector<float> pseudo_ranges, float distance_max,
                        float observation_stdev);


int main() {

    //set observation standard deviation:
    float observation_stdev = 1.0f;

    //number of x positions on map
    int map_size = 25;

    //set distance max
    float distance_max = map_size;

    //define landmarks
    std::vector<float> landmark_positions {5, 10, 12, 20};

    //define observations
    std::vector<float> observations {5.5, 13, 15};

    //step through each pseudo position x (i)
    for (unsigned int i = 0; i < map_size; ++i) {
        auto pseudo_position = float(i);

        //get pseudo ranges
        std::vector<float> pseudo_ranges = pseudo_range_estimator(landmark_positions,
                                                                  pseudo_position);

        //get observation probability
        float observation_prob = observation_model(landmark_positions, observations,
                                                   pseudo_ranges, distance_max,
                                                   observation_stdev);

        //print to stdout
        std::cout << observation_prob << endl;
    }

    return 0;
};

// Complete the observation model function
// calculates likelihood prob term based on landmark proximity
float observation_model(std::vector<float> landmark_positions, std::vector<float> observations,
                        std::vector<float> pseudo_ranges, float distance_max,
                        float observation_stdev) {

    float distance_prob = 1;

    if (pseudo_ranges.empty()) {
       distance_prob = 0;
    } else {
        for (int index = 0; index < observations.size(); index++) {
            float distance = distance_max;
            if (index < pseudo_ranges.size()) {
                distance = pseudo_ranges[index];
            }
            float p = Helpers::normpdf(distance, observations[index] , observation_stdev);
            distance_prob *= p;
        }
    }

    return distance_prob;


    /* Udacity solution:
     *

//observation model: calculates likelihood prob term based on landmark proximity
float observation_model(std::vector<float> landmark_positions, std::vector<float> observations,
                        std::vector<float> pseudo_ranges, float distance_max,
                        float observation_stdev) {

    //initialize observation probability:
    float distance_prob = 1.0f;

    //run over current observation vector:
    for (unsigned int z=0; z< observations.size(); ++z) {

        //define min distance:
        float pseudo_range_min;

        //check, if distance vector exists:
        if(pseudo_ranges.size() > 0) {
            //set min distance:
            pseudo_range_min = pseudo_ranges[0];
            //remove this entry from pseudo_ranges-vector:
            pseudo_ranges.erase(pseudo_ranges.begin());

        }

    //no or negative distances: set min distance to a large number:
    else {
        // Can use infinity or distance_max here
        pseudo_range_min = std::numeric_limits<const float>::infinity();

    }

        //estimate the probabiity for observation model, this is our likelihood:
        distance_prob *= Helpers::normpdf(observations[z], pseudo_range_min,
                                          observation_stdev);

    }
    return distance_prob;
}


     *
}

std::vector<float> pseudo_range_estimator(std::vector<float> landmark_positions,
                                          float pseudo_position) {

    // define pseudo observation vector:
    std::vector<float> pseudo_ranges;

    // loop over number of landmarks and estimate pseudo ranges:
        for (float landmark_position : landmark_positions) {

            //estimate pseudo range for each single landmark
            //and the current state position pose_i:
            float range_l = landmark_position - pseudo_position;

            //check if distances are positive:
            if (range_l > 0.0f) {
                pseudo_ranges.push_back(range_l);
            }
        }

    // sort pseudo range vector:
    sort(pseudo_ranges.begin(), pseudo_ranges.end());

    return pseudo_ranges;
}