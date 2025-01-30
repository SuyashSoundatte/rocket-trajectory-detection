#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#pragma once

#include <math.h>
#include <vector>
using namespace std;

class trajectory {
    public:
        // Constructor
        trajectory();

        // Methods
        float evaluateSigmoid(float x);
        void calculateTrajectory();
        void calculateDragTrajectory(); 
        bool checkFeasibleTrajectory();
        void resetTrajectory();

        // Variables
        vector<float> xvalues;
        vector<float> yvalues;
        vector<float> drag_xvalues;  
        vector<float> drag_yvalues;   
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
