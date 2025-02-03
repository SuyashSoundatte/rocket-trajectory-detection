#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class Trajectory {
public:
    // Constructor
    Trajectory();

    // Methods
    float evaluateSigmoid(float x);
    void calculateTrajectory();
    void calculateDragTrajectory();
    bool isFeasible();
    void resetTrajectory();
    void writeTrajectoryToFile(const std::string& filename, const std::vector<float>& xvalues, const std::vector<float>& yvalues);

    // Variables
    std::vector<float> xvalues;
    std::vector<float> yvalues;
    std::vector<float> drag_xvalues;
    std::vector<float> drag_yvalues;
    float height;
    float downrange;
    float minDistance;
    float trueDistance;
    float lat_start;
    float lon_start;
    float alt;
    float lat_end;
    float lon_end;
    float bearing;
    float los_angle;
    const float R;
    const int tangentFactor;
    float simTime;
    int nPoints;
};

#endif