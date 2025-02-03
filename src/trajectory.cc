#include "trajectory.h"

Trajectory::Trajectory() : R(6371000.0), tangentFactor(13), height(0), downrange(0), trueDistance(0), nPoints(0) {}

float Trajectory::evaluateSigmoid(float x) {
    if (height == 0) return 0;
    float value = 1 / (1 + exp(-(x - 0.5 * height) / (height / tangentFactor)));
    return downrange * value;
}

void Trajectory::calculateTrajectory() {
    int count = 0;
    xvalues.reserve(height / 50);
    yvalues.reserve(height / 50);
    for (int i = 0; i <= static_cast<int>(height); i += 50) {
        count++;
        xvalues.push_back(evaluateSigmoid(static_cast<float>(i)));
        yvalues.push_back(-static_cast<float>(i) + height);
        if (count >= 2) {
            trueDistance += std::sqrt(std::pow(xvalues[count - 1] - xvalues[count - 2], 2) + std::pow(yvalues[count - 1] - yvalues[count - 2], 2));
        }
    }
    if (!yvalues.empty() && yvalues.back() != 0) {
        xvalues.push_back(evaluateSigmoid(height));
        yvalues.push_back(0);
    }
    nPoints = xvalues.size();
}

void Trajectory::calculateDragTrajectory() {
    int count = 0;
    drag_xvalues.reserve(height / 50);
    drag_yvalues.reserve(height / 50);
    for (int i = 0; i <= static_cast<int>(height); i += 50) {
        count++;
        drag_xvalues.push_back(evaluateSigmoid(static_cast<float>(i)));
        drag_yvalues.push_back(-static_cast<float>(i) + height - 100);
        if (count >= 2) {
            trueDistance += std::sqrt(std::pow(drag_xvalues[count - 1] - drag_xvalues[count - 2], 2) + std::pow(drag_yvalues[count - 1] - drag_yvalues[count - 2], 2));
        }
    }
    if (!drag_yvalues.empty() && drag_yvalues.back() != 0) {
        drag_xvalues.push_back(evaluateSigmoid(height));
        drag_yvalues.push_back(0);
    }
}

bool Trajectory::isFeasible() {
    float phi1 = lat_start * (M_PI / 180.0);
    float phi2 = lat_end * (M_PI / 180.0);
    float lam1 = lon_start * (M_PI / 180.0);
    float lam2 = lon_end * (M_PI / 180.0);
    float dphi = phi2 - phi1;
    float dlam = lam2 - lam1;
    float a = std::pow(std::sin(dphi / 2), 2) + std::cos(phi1) * std::cos(phi2) * std::pow(std::sin(dlam / 2), 2);
    a = std::clamp(a, 0.0f, 1.0f);
    downrange = R * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    los_angle = std::atan(height / downrange) * (180 / M_PI);
    bearing = std::atan2(std::sin(dlam) * std::cos(phi2), std::cos(phi1) * std::sin(phi2) - std::sin(phi1) * std::cos(phi2) * std::cos(dlam)) * (180 / M_PI);
    minDistance = std::sqrt(std::pow(height, 2) + std::pow(downrange, 2));
    return los_angle >= 60.0;
}

void Trajectory::resetTrajectory() {
    xvalues.clear();
    yvalues.clear();
    drag_xvalues.clear();
    drag_yvalues.clear();
    nPoints = 0;
    trueDistance = 0;
    height = 0;
    downrange = 0;
}

void Trajectory::writeTrajectoryToFile(const std::string& filename, const std::vector<float>& xvalues, const std::vector<float>& yvalues) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open " << filename << " for writing!" << std::endl;
        return;
    }
    file << "x,y\n";
    for (size_t i = 0; i < xvalues.size(); ++i) {
        file << xvalues[i] << "," << yvalues[i] << "\n";
    }
}