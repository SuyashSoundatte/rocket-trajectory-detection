#include <iostream>
#include <fstream>
#include "trajectory.h"

int main() {
    // Create a trajectory object
    trajectory traj;

    // Initialize trajectory parameters
    traj.height = 35500;  // Height of the trajectory (e.g., meters)
    traj.lat_start = 28.660;  // Starting latitude (e.g., Los Angeles)
    traj.lon_start = -79.969;  // Starting longitude
    traj.lat_end = 28.870;  // Ending latitude (e.g., California Central Point)
    traj.lon_end = -80.167;  // Ending longitude

    // Check if the trajectory is feasible
    if (traj.checkFeasibleTrajectory()) {
        std::cout << "Trajectory is feasible." << std::endl;

        // Calculate the landing trajectory
        traj.calculateTrajectory();

        // Write the landing trajectory data to a file
        std::ofstream file("trajectory_data.csv");
        file << "x,y\n";  // CSV header
        for (size_t i = 0; i < traj.xvalues.size(); ++i) {
            file << traj.xvalues[i] << "," << traj.yvalues[i] << "\n";
        }
        file.close();

        // Calculate the drag trajectory
        traj.calculateDragTrajectory();

        // Write the drag trajectory data to a file
        std::ofstream drag_file("trajectory_with_drag.csv");
        drag_file << "x,y\n";  // CSV header
        for (size_t i = 0; i < traj.drag_xvalues.size(); ++i) {
            drag_file << traj.drag_xvalues[i] << "," << traj.drag_yvalues[i] << "\n";
        }
        drag_file.close();

        std::cout << "Landing and Drag trajectories exported to CSV files." << std::endl;
    } else {
        std::cout << "Trajectory is not feasible." << std::endl;
        std::cout << "Line-of-sight angle: " << traj.los_angle << " degrees" << std::endl;
    }

    // Reset the trajectory
    traj.resetTrajectory();
    std::cout << "Trajectory reset. Number of points: " << traj.nPoints << std::endl;

    return 0;
}
