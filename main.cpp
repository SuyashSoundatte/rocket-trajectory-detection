#include <iostream>
#include <fstream>
#include "trajectory.h"

int main() {
    // Create a trajectory object
    trajectory traj;

    // Initialize trajectory parameters
    traj.height = 35500;     // Height of the trajectory (e.g., meters)
    traj.lat_start = 28.660; // Starting latitude (e.g., Los Angeles)
    traj.lon_start = -79.969; // Starting longitude
    traj.lat_end = 28.870;   // Ending latitude (e.g., California Central Point)
    traj.lon_end = -80.167; // Ending longitude

    // Check if the trajectory is feasible
    if (traj.checkFeasibleTrajectory()) {
        std::cout << "Trajectory is feasible." << std::endl;

        // Calculate the trajectory
        traj.calculateTrajectory();

        // Write trajectory data to a file
        std::ofstream file("trajectory_data.csv");
        file << "x,y\n"; // CSV header
        for (size_t i = 0; i < traj.xvalues.size(); ++i) {
            file << traj.xvalues[i] << "," << traj.yvalues[i] << "\n";
        }
        file.close();

        std::cout << "Trajectory data exported to 'trajectory_data.csv'" << std::endl;
    } else {
        std::cout << "Trajectory is not feasible." << std::endl;
        std::cout << "Line-of-sight angle: " << traj.los_angle << " degrees" << std::endl;
    }

    // Reset the trajectory
    traj.resetTrajectory();
    std::cout << "Trajectory reset. Number of points: " << traj.nPoints << std::endl;

    return 0;
}
