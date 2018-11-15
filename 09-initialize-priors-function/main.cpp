#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev);

int main() {

  //set standard deviation of position:
  float position_stdev = 1.0f;

  //set map horizon distance in meters
  int map_size = 25;

  //initialize landmarks
  std::vector<float> landmark_positions {5, 10, 20};

  // initialize priors
  std::vector<float> priors = initialize_priors(map_size, landmark_positions,
                                                position_stdev);

  //print values to stdout
  for (unsigned int p = 0; p < priors.size(); p++) {
    std::cout << priors[p] << endl;
  }

  return 0;

};

// Complete the initialize_priors function
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev) {

  // initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev

  // set all priors to 0.0
  std::vector<float> priors(map_size, 0.0);

  // determine init p
  float init_p = 1.0f / (landmark_positions.size() * (1 + 2 * (position_stdev)));

  for(int index = 0; index < landmark_positions.size(); index++) {
    for(int index_landmark = landmark_positions[index] - position_stdev; index_landmark <= landmark_positions[index] + position_stdev; index_landmark++) {
      priors[index_landmark] = init_p;
    }
  }

  return priors;
}
