#include <iostream>
#include <fstream>
#include "trajectory.h"

int main() {
    Trajectory traj;
    traj.height = 35500;
    traj.lat_start = 28.660;
    traj.lon_start = -79.969;
    traj.lat_end = 28.870;
    traj.lon_end = -80.167;

    if (traj.isFeasible()) {
        std::cout << "Trajectory is feasible." << std::endl;
        traj.calculateTrajectory();
        traj.writeTrajectoryToFile("trajectory_data.csv", traj.xvalues, traj.yvalues);
        traj.calculateDragTrajectory();
        traj.writeTrajectoryToFile("trajectory_with_drag.csv", traj.drag_xvalues, traj.drag_yvalues);
        std::cout << "Landing and Drag trajectories exported to CSV files." << std::endl;
    } else {
        std::cout << "Trajectory is not feasible." << std::endl;
        std::cout << "Line-of-sight angle: " << traj.los_angle << " degrees" << std::endl;
    }
    traj.resetTrajectory();
    std::cout << "Trajectory reset. Number of points: " << traj.nPoints << std::endl;
    return 0;
}