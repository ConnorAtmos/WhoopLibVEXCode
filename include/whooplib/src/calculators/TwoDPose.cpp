/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       TwoDPose.cpp                                              */
/*    Author:       Connor White (WHOOP)                                      */
/*    Created:      Thu Jun 21 2024                                           */
/*    Description:  Two-Dimensional CFrames                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "whooplib/include/calculators/TwoDPose.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>
#include "whooplib/include/toolbox.hpp"

TwoDPose::TwoDPose(double x, double y, double yaw) {
    this->x = x;
    this->y = y;
    this->yaw = yaw;
}

TwoDPose TwoDPose::global_xy_delta_only(const TwoDPose& other) const{
    // Calculate the new position, preserving yaw
    TwoDPose result = toWorldSpace(other);
    result.yaw = this->yaw;

    return result;
}

TwoDPose TwoDPose::operator*(const TwoDPose& other) const {
    return toWorldSpace(other);
}

TwoDPose& TwoDPose::operator*=(const TwoDPose& other) {
    *this = *this * other;
    return *this;
}

TwoDPose TwoDPose::toObjectSpace(const TwoDPose& other) const {
    return this->toObjectSpace(other.x, other.y, other.yaw);
}

TwoDPose TwoDPose::toObjectSpace(double x, double y, double yaw) const {
    // Calculate the relative position
    double dx = x - this->x;
    double dy = y - this->y;

    // Create the rotation matrix for -yaw
    double cos_yaw = cos(this->yaw);
    double sin_yaw = sin(this->yaw);
    
    // Apply the rotation matrix
    double relative_x = dx * sin_yaw - dy * cos_yaw;
    double relative_y = dx * cos_yaw + dy * sin_yaw; 

    // Calculate the relative yaw
    double relative_yaw = normalize_angle(denormalize_angle(yaw) - denormalize_angle(this->yaw));

    return TwoDPose(relative_x, relative_y, relative_yaw);
}

TwoDPose TwoDPose::operator-() const {
    return TwoDPose(-x, -y, -yaw);
}


TwoDPose TwoDPose::toWorldSpace(const TwoDPose& other) const {
    // Apply rotation to the point using this object's yaw
    double this_yaw_safe = std::abs(this->yaw) < 1e-10 ? 1e-10 : this->yaw;

    double const cos_yaw = cos(this_yaw_safe);
    double const sin_yaw = sin(this_yaw_safe);

    double global_x = this->x + other.x * sin_yaw + other.y * cos_yaw;
    double global_y = this->y - other.x * cos_yaw + other.y * sin_yaw;

    double global_yaw = normalize_angle(denormalize_angle(this->yaw) + denormalize_angle(other.yaw));

    return TwoDPose(global_x, global_y, global_yaw);
}


std::string TwoDPose::to_string(int decimal_places) {
    std::ostringstream oss;
    if (decimal_places >= 0) {
        oss << std::fixed << std::setprecision(decimal_places);
    }
    oss << x << " " << y << " " << yaw;
    return oss.str();
}

std::string TwoDPose::to_realsense_string(int decimal_places) {
    std::ostringstream oss;
    if (decimal_places >= 0) {
        oss << std::fixed << std::setprecision(decimal_places);
    }
    oss << -y << " " << -x << " " << yaw;
    return oss.str();
}