#include "trajectory.h"

trajectory::trajectory():R(6371000.0), tangentFactor(13){
    trueDistance = 0;
}

float trajectory::evaluateSigmoid(float x){
    float value = 1/(1 + exp(-(x-0.5*height)/(height/tangentFactor)));
    return downrange*value;
}

void trajectory::calculateTrajectory(){
    int count = 0;
    for (int i = 0; i <= (int)height; i+=50){
        count++;
        xvalues.push_back(evaluateSigmoid((float)i));
        yvalues.push_back(-(float)i + height);
        if(count >= 2){
            trueDistance += sqrt(pow(xvalues[count -1]-xvalues[count-2], 2) + (pow(yvalues[count -1]-yvalues[count-2], 2)));
        }
    }
    if(yvalues.back() != 0){
        xvalues.push_back(evaluateSigmoid((float)height));
        yvalues.push_back(0);
    }
    nPoints = xvalues.size();
}

void trajectory::resetTrajectory(){
    xvalues.clear();
    yvalues.clear();
    nPoints = 0;
    trueDistance = 0;
    height = 0;
    downrange = 0;
}

bool trajectory::checkFeasibleTrajectory(){
    float phi1 = lat_start*(M_PI/180.0);
    float phi2 = lat_end*(M_PI/180.0);
    float lam1 = lon_start*(M_PI/180.0);
    float lam2 = lon_end*(M_PI/180.0);
    float dphi = phi2 - phi1;
    float dlam = lam2 - lam1;
    float a= pow(sin(dphi/2), 2) + cos(phi1)*cos(phi2)*pow(sin(dlam/2), 2);
    downrange = R*atan2(sqrt(a), sqrt(1-a));
    los_angle = atan(height/downrange)*(180/M_PI);
    bearing = (atan2(sin(dlam)*cos(phi2), cos(phi1)*sin(phi2) - sin(phi1)*cos(phi2)*cos(dlam)))*(180/M_PI);
    minDistance = sqrt(pow(height, 2) + pow((downrange), 2));
    if(los_angle < 60.0){
        return false;
    }
    return true;
}