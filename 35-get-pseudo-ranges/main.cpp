#include <iostream>
#include <algorithm>
#include <vector>

#include "helpers.h"
using namespace std;

// set standard deviation of control:
float control_stdev = 1.0f;

// meters vehicle moves per time step
float movement_per_timestep = 1.0f;

// number of x positions on map
int map_size = 25;

// define landmarks
std::vector<float> landmark_positions {5, 10, 12, 20};



std::vector<float> pseudo_range_estimator(std::vector<float> landmark_positions, float pseudo_position);


int main() {

    // step through each pseudo position x (i)
    for (unsigned int i = 0; i < map_size; ++i) {
        auto pseudo_position = float(i);
        // get pseudo ranges
        std::vector<float> pseudo_ranges = pseudo_range_estimator(landmark_positions, pseudo_position);

       // print to stdout
        if (!pseudo_ranges.empty()) {
            for (float pseudo_range : pseudo_ranges) {
                std::cout << "x: " << i << "\t" << pseudo_range << endl;
            }
            std::cout << "-----------------------" << endl;
        }
    }

    return 0;
};

// Complete pseudo range estimator function
std::vector<float> pseudo_range_estimator(std::vector<float> landmark_positions, float pseudo_position) {

    // define pseudo observation vector:
    std::vector<float> pseudo_ranges;

    // loop over number of landmarks and estimate pseudo ranges:
    for (float landmark_position : landmark_positions) {
        float delta = landmark_position - pseudo_position;
        if (delta > 0) {
           pseudo_ranges.push_back(delta);
        }
    }

    // sort pseudo range vector:
    std::sort(pseudo_ranges.begin(), pseudo_ranges.end());

    return pseudo_ranges;
}

/*
 * udacity solution:
 *
 *
 * /loop over number of landmarks and estimate pseudo ranges:
        for (unsigned int l=0; l< landmark_positions.size(); ++l) {

            //estimate pseudo range for each single landmark
            //and the current state position pose_i:
            float range_l = landmark_positions[l] - pseudo_position;

            //check if distances are positive:
            if (range_l > 0.0f) {
                pseudo_ranges.push_back(range_l);
            }
        }

    //sort pseudo range vector:
    sort(pseudo_ranges.begin(), pseudo_ranges.end());
 *
 */