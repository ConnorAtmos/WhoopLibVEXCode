/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       WhoopInertial.hpp                                         */
/*    Author:       Connor White (WHOOP)                                      */
/*    Created:      Thu Jun 21 2024                                           */
/*    Description:  Virtual Interial Sensor that Follow Robotic Standard      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef WHOOP_INERTIAL_HPP
#define WHOOP_INERTIAL_HPP

#include "vex.h"

/**
 * Manages an inertial sensor to provide orientation and motion-related data.
 */
class WhoopInertial {
protected:
    double yaw_offset = 0; // Offset to adjust the yaw reading to account for initial orientation.
    bool is_reversed = false; // Flag to indicate if the sensor readings should be reversed.
public:
    inertial vex_inertial; // VEX Robotics Inertial Sensor object.

    /**
     * Constructor to initialize an inertial sensor on a specified port.
     * @param port The port number where the inertial sensor is connected.
     */
    WhoopInertial(std::int32_t port); 

    /**
     * Constructor to initialize an inertial sensor on a specified port with an option to reverse the readings.
     * @param port The port number where the inertial sensor is connected.
     * @param reversed Boolean to set if the sensor readings should be reversed (true) or not (false).
     */
    WhoopInertial(std::int32_t port, bool reversed); 

    /**
     * Retrieves the current yaw value with any applied offsets, in degrees by default.
     * @return The yaw value in degrees.
     */
    double get_yaw(); // Degrees is default

    /**
     * Explicitly retrieves the current yaw value in degrees.
     * @return The yaw value in degrees.
     */
    double get_yaw_degrees();

    /**
     * Retrieves the current yaw value in radians.
     * @return The yaw value in radians.
     */
    double get_yaw_radians();

    /**
     * Retrieves the current roll value with any applied offsets, in degrees by default.
     * @return The roll value in degrees.
     */
    double get_roll();

    /**
     * Explicitly retrieves the current roll value in degrees.
     * @return The roll value in degrees.
     */
    double get_roll_degrees();

    /**
     * Retrieves the current roll value in radians.
     * @return The roll value in radians.
     */
    double get_roll_radians(); // Gets roll in radians

    /**
     * Retrieves the current pitch value with any applied offsets, in degrees by default.
     * @return The pitch value in degrees.
     */
    double get_pitch(); // Gets pitch in degrees

    /**
     * Explicitly retrieves the current pitch value in degrees.
     * @return The pitch value in degrees.
     */
    double get_pitch_degrees(); // Gets pitch in degrees, explicit

    /**
     * Retrieves the current pitch value in radians.
     * @return The pitch value in radians.
     */
    double get_pitch_radians(); // Gets pitch in radians

    /**
     * Initiates calibration of the inertial sensor. This process may take a few seconds.
     */
    void calibrate();

    /**
     * Resets the yaw reading to zero or to a specified orientation in degrees.
     */
    void tare();

    /**
     * Resets the yaw reading to a specific orientation in degrees.
     * @param degrees The angle in degrees to which the yaw should be set.
     */
    void tare(double degrees); // Degrees is default

    /**
     * Resets the yaw reading to a specific orientation, specified in degrees.
     * @param degrees The angle in degrees to which the yaw should be set.
     */
    void tare_degrees(double degrees);

    /**
     * Resets the yaw reading to a specific orientation, specified in radians.
     * @param radians The angle in radians to which the yaw should be set.
     */
    void tare_radians(double radians);
};


#endif // WHOOP_INERTIAL_HPP

