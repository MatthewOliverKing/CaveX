////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019
// Commonwealth Scientific and Industrial Research Organisation (CSIRO)
// ABN 41 687 119 230
//
// Author: Fletcher Talbot
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SYROPOD_HIGHLEVEL_CONTROLLER_STANDARD_INCLUDES_H
#define SYROPOD_HIGHLEVEL_CONTROLLER_STANDARD_INCLUDES_H

#include <ros/ros.h>
#include <ros/console.h>
#include <ros/assert.h>
#include <ros/exceptions.h>

#include <dynamic_reconfigure/server.h>

#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/UInt16.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Joy.h>

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/TransformStamped.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/static_transform_broadcaster.h>

#include <Eigen/StdVector>
#include <Eigen/Geometry>

#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#define UNASSIGNED_VALUE double(INT_MAX) ///< Value used to determine if variable has been assigned
#define PROGRESS_COMPLETE 100            ///< Value denoting 100% and a completion of progress of various functions
#define THROTTLE_PERIOD 5                ///< Default throttle period for all throttled rosconsole messages (seconds)

#define UNDEFINED_ROTATION Eigen::Quaterniond(0, 0, 0, 0)
#define UNDEFINED_POSITION Eigen::Vector3d(double(INT_MAX), double(INT_MAX), double(INT_MAX))

#define GRAVITY_ACCELERATION -9.81 ///< Approximate gravitational acceleration (m/s/s)

/// Converts Degrees to Radians.
/// @param[in] degrees Value in degrees to be converted to radians
/// @return Value converted to radians from degrees
inline double degreesToRadians(const double &degrees) { return degrees / 360.0 * 2.0 * M_PI; }

/// Converts Radians to Degrees.
/// @param[in] radians Value in radians to be converted to degrees
/// @return Value converted to degrees from radians
inline double radiansToDegrees(const double& radians) { return (radians / (2.0 * M_PI)) * 360.0; }

/// Performs the modulo operation with adherence to Euclidean division.
/// @param[in] a The dividend for the operation
/// @param[in] b The divisor for the operation
/// @return The result after performing modulo operation with adherence to Euclidean division
template <class T>
inline T mod(const T& a, const T& b) { return (a % b + b) % b; }

/// Performs the square operation.
/// @param[in] val The value to be squared
/// @return The result after squaring the value
template <class T>
inline T sqr(const T& val) { return val * val; }

/// Returns 1 or -1 depending on the sign of the input.
/// @param[in] val The input value
/// @return 1 or -1 depending on the sign of the input
template <class T>
inline T sign(const T& val) { return (val > 0 ? 1 : -1); }

/// Rounds the input number to the nearest integer.
/// @param[in] x The input number
/// @return Nearest integer to the input number
inline int roundToInt(const double& x) { return (x >= 0 ? int(x + 0.5) : -int(0.5 - x)); }

/// Rounds the input number to the nearest EVEN integer.
/// @param[in] x The input number
/// @return Nearest even integer to the input number
inline int roundToEvenInt(const double& x) { return (int(x) % 2 == 0 ? int(x) : int(x) + 1); }

/// Returns the input value 'clamped' within min and max limits.
/// @param[in] value The input value
/// @param[in] min_value The minimum limit
/// @param[in] max_value The maximum limit
/// @return The input value clamped within min and max limits
template <class T>
inline T clamped(const T& value, const T& min_value, const T& max_value)
{
  ROS_ASSERT(min_value <= max_value);
  return std::max(min_value, std::min(value, max_value));
}

/// Returns the input vector scaled such that the magnitude does not exceed the input magnitude.
/// @param[in] value The input vector
/// @param[in] magnitude The maximum magnitude
/// @return The input vector scaled such that the magnitude does not exceed the input magnitude
template <class T>
inline T clamped(const T& value, const double& magnitude)
{
  return value.norm() > magnitude ? (value * (magnitude / value.norm())) : value;
}

/// Returns the input vector scaled such that each element does not exceed the magnitude of each element of the limit
/// vector.
/// @param[in] value The input vector
/// @param[in] limit The limit vector
/// @return The input vector scaled such that each element does not exceed the magnitude of each element of the limit
/// vector
template <class T>
inline T clamped(const T& value, const T& limit)
{
  Eigen::VectorXd result(value.size());
  for (int i = 0; i < value.size(); ++i)
  {
    result[i] = clamped(value[i], -limit[i], limit[1]);
  }
  return result;
}

/// Returns the input value with a precision defined by the precision input. (Eg: 1.00001 @ precision = 3 -> 1.000)
/// @param[in] value The input value
/// @param[in] precision The required precision
/// @return The input value with a precision defined by the precision input
inline double setPrecision(const double& value, const int& precision)
{
  return roundToInt(value * pow(10, precision)) / pow(10, precision);
}

/// Returns the input vector with a precision defined by the precision input. (Eg: 1.00001 @ precision = 3 -> 1.000)
/// @param[in] vector The input vector
/// @param[in] precision The required precision
/// @return The input vector with a precision defined by the precision input
inline Eigen::Vector3d setPrecision(const Eigen::Vector3d& vector, const int& precision)
{
  return Eigen::Vector3d(roundToInt(vector[0] * pow(10, precision)) / pow(10, precision),
                  roundToInt(vector[1] * pow(10, precision)) / pow(10, precision),
                  roundToInt(vector[2] * pow(10, precision)) / pow(10, precision));
}

/// Converts a linear control input (0.0 to 1.0) to a smoothed signal using the SmoothStep function.
/// (https://en.wikipedia.org/wiki/Smoothstep)
/// @param[in] control_input The linear control input from 0.0 to 1.0
/// @return The output of the control input run through a smoothStep function
inline double smoothStep(const double& control_input)
{
  return (6.0*pow(control_input, 5) - 15.0*pow(control_input, 4) + 10.0*pow(control_input, 3));
}

/// Calculates the projection vector of an input vector onto a reference vector.
/// (en.wikipedia.org/wiki/Vector_projection)
/// @param[in] a The input vector
/// @param[in] b The reference vector
/// @return The resultant projection vector
inline Eigen::Vector3d getProjection(const Eigen::Vector3d& a, const Eigen::Vector3d& b)
{
  if (a.norm() == 0.0 || b.norm() == 0.0)
  {
    return Eigen::Vector3d::Zero();
  }
  else
  {
    return (a.dot(b) / b.dot(b))*b;
  }
}

/// Calculates the rejection vector of an input vector onto a reference vector.
/// (en.wikipedia.org/wiki/Vector_projection)
/// @param[in] a The input vector
/// @param[in] b The reference vector
/// @return The resultant rejection vector
inline Eigen::Vector3d getRejection(const Eigen::Vector3d& a, const Eigen::Vector3d& b)
{
  return a - getProjection(a, b);
}

/// Returns the linear interpolation between origin and target defined by the control input
/// @param[in] origin The origin of the linear interpolation (control input == 0.0)
/// @param[in] target The target of the linear interpolation (control_input == 1.0)
/// @param[in] control_input The input determining the interpolation point between origin and target
/// @return The resultant linear interpolation value
template <class T>
inline T interpolate(const T& origin, const T& target, const double& control_input)
{
  ROS_ASSERT(control_input >= 0.0 && control_input <= 1.0);
  return (1.0 - control_input) * origin + control_input * target;
}

/// Return rotation with shorter path between identical rotations on quaternion.
/// @param[in] test The test rotation to check for shorter rotation path
/// @param[in] reference The reference rotation for the target rotation
/// @return Rotation with shorter path between identical rotations on quaternion
inline Eigen::Quaterniond correctRotation(const Eigen::Quaterniond& test, const Eigen::Quaterniond& reference)
{
  if (test.dot(reference) < 0.0)
  {
    return Eigen::Quaterniond(-test.w(), -test.x(), -test.y(), -test.z());
  }
  else
  {
    return test;
  }
}

/// Converts Euler Angles (intrisic or extrinsic roll/pitch/yaw order) to Eigen Quaternion
/// @param[in] euler Eigen Vector3d of Euler angles (roll, pitch, yaw) to be converted
/// @param[in] intrinsic Defines whether conversion occurs intrinsically or extrinsically
/// @return Eigen Quaternion generated using given Euler Angles
inline Eigen::Quaterniond eulerAnglesToQuaternion(const Eigen::Vector3d& euler, const bool& intrinsic = false)
{
  if (intrinsic)
  {
    return Eigen::Quaterniond(Eigen::AngleAxisd(euler[0], Eigen::Vector3d::UnitX()) *
                       Eigen::AngleAxisd(euler[1], Eigen::Vector3d::UnitY()) *
                       Eigen::AngleAxisd(euler[2], Eigen::Vector3d::UnitZ()));
  }
  else
  {
    return Eigen::Quaterniond(Eigen::AngleAxisd(euler[2], Eigen::Vector3d::UnitZ()) *
                       Eigen::AngleAxisd(euler[1], Eigen::Vector3d::UnitY()) *
                       Eigen::AngleAxisd(euler[0], Eigen::Vector3d::UnitX()));
  }
}

/// Converts Eigen Quaternion to Euler angles (intrinsic or extrinsic roll/pitch/yaw order) and enures values are in the
/// range -PI:PI.
/// @param[in] rotation Eigen Quaterniond of rotation to be converted
/// @param[in] intrinsic Defines whether conversion occurs intrinsically or extrinsically
/// @return Euler Angles generated using given Eigen Quaternoid
inline Eigen::Vector3d quaternionToEulerAngles(const Eigen::Quaterniond& rotation, const bool& intrinsic = false)
{
  Eigen::Vector3d result(0,0,0);
  
  // Intrinsic rotation (roll, pitch, yaw order)
  if (intrinsic)
  {
    result = rotation.toRotationMatrix().eulerAngles(0,1,2);
  }
  // Extrinsic rotation (equivalent to intrinsic using opposite (yaw, pitch, roll) order)
  else
  {
    result = rotation.toRotationMatrix().eulerAngles(2,1,0);
  }
  
  /// RotationMatrix::eulerAngles returns values in the ranges [0:PI, -PI:PI, -PI:PI] which means that in order to
  /// represent a rotation smaller than zero about the first axis, the first axis is pointed in the opposite direction
  /// and is then flipped around using the 2nd and 3rd axes (i.e. 2nd and 3rd axes += PI). The resultant euler rotation
  /// is correct but results in angles outside the desired range of -PI:PI. The following code checks if this flipping
  /// occurs by checking is the angles of the 2nd and 3rd axes are greater than PI/2. If so all resultant euler
  /// angles are modified such that they range between -PI:PI.

  if ((abs(result[1]) > M_PI / 2 || abs(result[2]) > M_PI / 2)) //Flipped
  {
    result[0] -= M_PI;
    if (result[1] > M_PI/2.0)
    {
      result[1] = -result[1] + M_PI;
    }
    else if (result[1] < M_PI/2.0)
    {
      result[1] = -result[1] - M_PI;
    }
    if (result[2] > M_PI/2.0)
    {
      result[2] -= M_PI;
    }
    else if (result[2] < M_PI/2.0)
    {
      result[2] += M_PI;
    }
  }
  return intrinsic ? result : Eigen::Vector3d(result[2], result[1], result[0]);
}

/// Returns a string representation of the input value.
/// @param[in] number The input value
/// @return String representation of the input value
template <typename T>
inline std::string numberToString(const T &number)
{
  std::ostringstream ss;
  ss << number;
  return ss.str();
}

/// Returns a string formatted using the same input arguments as rosconsole.
/// @param[in] format The input string
/// @param[in] args The list of arguments to populate the format string
/// @return Formatted string using the input and the list of arguments
template <typename... Args>
inline std::string stringFormat(const std::string &format, Args... args)
{
  size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

///  Returns a vector representing a 3d point at a given time input along a 2nd order bezier curve defined by input
///  control nodes.
///  @param[in] points An array of control node vectors.
///  @param[in] t A time input from 0.0 to 1.0.
template <class T>
inline T quadraticBezier(const T *points, const double &t)
{
  double s = 1.0 - t;
  return points[0] * (s * s) + points[1] * (2.0 * t * s) + points[2] * (t * t);
}

/// Returns a vector representing a 3d point at a given time input along a 2nd order bezier curved. The generated point
/// is on a curve that is guided to pass through the defined control points.
/// @param[in] points An array of control node vectors.
/// @param[in] t A time input from 0.0 to 1.0.
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline Eigen::Vector3d quadraticBezierCurveThroughControlPoint(const T *points, const double &t)
{
  double s = 1.0 - t;
  return (points[1] - points[0] * (s * s) - points[2] * (t * t)) /
         (2.0 * t * s);
}

/// Returns a vector representing a 3d point at a given time input along a 3rd order bezier curve defined by input
/// control nodes.
/// @param[in] points An array of control node vectors
/// @param[in] t A time input from 0.0 to 1.0
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline T cubicBezier(const T* points, const double& t)
{
  double s = 1.0 - t;
  return points[0] * (s * s * s) + points[1] * (3.0 * t * s * s) + points[2] * (3.0 * t * t * s) +
         points[3] * (t * t * t);
}

/// Returns a vector representing a 3d point at a given time input along the derivative of a 3rd order bezier curve
/// defined by input control nodes.
/// @param[in] points An array of control node vectors
/// @param[in] t A time input from 0.0 to 1.0
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline T cubicBezierDot(const T* points, const double& t)
{
  double s = 1.0 - t;
  return (3 * s * s * (points[1] - points[0]) + 6 * s * t * (points[2] - points[1]) +
          3 * t * t * (points[3] - points[2]));
}

/// Returns a vector representing a 3d point at a given time input along a 3rd order bezier curved. The generated point
/// is on a curve that is guided to pass through the defined control points.
/// @param[in] points An array of control node vectors.
/// @param[in] t A time input from 0.0 to 1.0.
/// @param[in] control_point_selection The control point that is being selected to have the curve passed through.
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline Eigen::Vector3d cubicBezierCurveThroughControlPoint(const T *points, const double &t, const unsigned int &control_point_selection)
{
  double s = 1.0 - t;
  if (control_point_selection == 1)
  {
    return (points[1] - points[0] * (s * s * s) - points[2] * (3.0 * t * t * s) -
            points[3] * (t * t * t)) /
           (3.0 * t * s * s);
  }
  else if (control_point_selection == 2)
  {
    return (points[2] - points[0] * (s * s * s) - points[1] * (3.0 * t * s * s) -
            points[3] * (t * t * t)) /
           (3.0 * t * t * s);
  }
  else
  {
    ROS_WARN("Something terribly wrong is happening. New Control points for the Cubic Bezier is NOT being generated as expected.");
    return Eigen::Vector3d(0, 0, 0);
  }
}

/// Returns a vector representing a 3d point at a given time input along a 4th order bezier curve defined by input
/// control nodes.
/// @param[in] points An array of control node vectors
/// @param[in] t A time input from 0.0 to 1.0
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline T quarticBezier(const T* points, const double& t)
{
  double s = 1.0 - t;
  return points[0] * (s * s * s * s) + points[1] * (4.0 * t * s * s * s) + points[2] * (6.0 * t * t * s * s) +
         points[3] * (4.0 * t * t * t * s) + points[4] * (t * t * t * t);
}

/// Returns a vector representing a 3d point at a given time input along the derivative of a 4th order bezier curve
/// defined by input control nodes.
/// @param[in] points An array of control node vectors
/// @param[in] t A time input from 0.0 to 1.0
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline T quarticBezierDot(const T* points, const double& t)
{
  double s = 1.0 - t;
  return (4.0 * s * s * s * (points[1] - points[0]) + 12.0 * s * s * t * (points[2] - points[1]) +
          12.0 * s * t * t * (points[3] - points[2]) + 4.0 * t * t * t * (points[4] - points[3]));
}

/// Returns a vector representing a 3d point at a given time input along a 4th order bezier curve defined by input
/// control nodes. Depending on the complexity of the target curve, it will generate points that will pass through
/// the defined control points. If the target curve is too complex the generate point will approximately go near
/// the control points. This behaviour is especially true for the 2nd control point.Iit's recommended to split
/// the curve into different parts and use the lower order Bezier curves.
/// @param[in] points An array of control node vectors.
/// @param[in] t A time input from 0.0 to 1.0.
/// @param[in] control_point_selection The control point that is being selected to have the curve passed through.
/// @return Vector representation generated using the given input array of control node vectors and the time input
template <class T>
inline Eigen::Vector3d quarticBezierCurveThroughControlPoint(const T *points, const double &t, const unsigned int &control_point_selection)
{
  double s = 1.0 - t;
  if (control_point_selection == 1)
  {
    return (points[1] - points[0] * (s * s * s * s) - points[2] * (6.0 * t * t * s * s) -
            points[3] * (4.0 * t * t * t * s) - points[4] * (t * t * t * t)) /
           (4.0 * t * s * s * s);
  }
  else if (control_point_selection == 2)
  {
    return (points[2] - points[0] * (s * s * s * s) - points[1] * (4.0 * t * s * s * s) -
            points[3] * (4.0 * t * t * t * s) - points[4] * (t * t * t * t)) /
           (6.0 * t * t * s * s);
  }
  else if (control_point_selection == 3)
  {
    return (points[3] - points[0] * (s * s * s * s) - points[1] * (4.0 * t * s * s * s) -
            points[2] * (6.0 * t * t * s * s) - points[4] * (t * t * t * t)) /
           (4.0 * t * t * t * s);
  }
  else
  {
    ROS_WARN("Something terribly wrong. New Control points for the Quartic Bezier is NOT being generated as expected.");
    return Eigen::Vector3d(0, 0, 0);
  }
}

/// Generates a classical Denavit–Hartenberg (DH) matrix from DH parameters.
/// @param[in] d The DH parameter representing offset along previous z-axis to the common normal
/// @param[in] theta The DH parameter representing angle about previous z axis, from old x-axis to new x-axis
/// @param[in] r The DH parameter representing length of the common normal
/// @param[in] alpha The DH parameter representing angle about common normal, form old z-axis to new z-axis
/// @return Classical Denavit-Hartenberg (DH) matrix generated using the given DH parameters as input
inline Eigen::Matrix4d createDHMatrix(const double& d, const double& theta, const double& r, const double& alpha)
{
  Eigen::Matrix4d m;
  m << cos(theta), -sin(theta)*cos(alpha),  sin(theta)*sin(alpha), r* cos(theta),
  sin(theta),  cos(theta)*cos(alpha), -cos(theta)*sin(alpha), r* sin(theta),
  0,             sin(alpha),             cos(alpha),            d,
  0,                      0,                      0,            1;
  return m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SYROPOD_HIGHLEVEL_CONTROLLER_STANDARD_INCLUDES_H

