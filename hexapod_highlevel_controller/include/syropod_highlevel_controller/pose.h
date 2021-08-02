////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019
// Commonwealth Scientific and Industrial Research Organisation (CSIRO)
// ABN 41 687 119 230
//
// Author: Fletcher Talbot
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SYROPOD_HIGHLEVEL_CONTROLLER_POSE_H
#define SYROPOD_HIGHLEVEL_CONTROLLER_POSE_H

#include "standard_includes.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class defining a 3d position and rotation using Eigen Vector3 and Quaternion classes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Pose
{
public:
  /// Blank contructor
  inline Pose(void) {};
  
  /// Pose class constructor.
  /// @param[in] position The vector input to be set as the position vector of the pose
  /// @param[in] rotation The vector input to be set as the rotation vector of the pose
  inline Pose(const Eigen::Vector3d& position, const Eigen::Quaterniond& rotation)
  {
    position_ = position;
    rotation_ = rotation;
  };
  
  /// Pose class constructor for geometry_msgs/Pose.
  /// @param[in] pose The geometry_msgs/Pose input to be set as the pose
  inline Pose(const geometry_msgs::Pose& pose)
  {
    position_ = Eigen::Vector3d(pose.position.x, pose.position.y, pose.position.z);
    rotation_ = Eigen::Quaterniond(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
  };
  
  /// Checks for NaN values within pose elements.
  /// @return Bool denoting whether pose contains no NaN values
  inline bool isValid(void)
  {
    return abs(position_[0]) < UNASSIGNED_VALUE &&
           abs(position_[1]) < UNASSIGNED_VALUE &&
           abs(position_[2]) < UNASSIGNED_VALUE &&
           abs(rotation_.w()) < UNASSIGNED_VALUE &&
           abs(rotation_.x()) < UNASSIGNED_VALUE &&
           abs(rotation_.y()) < UNASSIGNED_VALUE &&
           abs(rotation_.z()) < UNASSIGNED_VALUE;
  }
  
  /// Pose class constructor for geometry_msgs/Transform.
  /// @param[in] transform The geometry_msgs/Transform input to be used to construct the pose
  inline Pose(const geometry_msgs::Transform& transform)
  {
    position_ = Eigen::Vector3d(transform.translation.x, transform.translation.y, transform.translation.z);
    rotation_ = Eigen::Quaterniond(transform.rotation.w,
                                   transform.rotation.x,
                                   transform.rotation.y,
                                   transform.rotation.z);
  };
  
  /// Returns a conversion of this pose object into a geometry_msgs::Pose.
  /// @return The converted geometry_msgs::Pose message
  inline geometry_msgs::Pose toPoseMessage(void)
  {
    geometry_msgs::Pose pose;
    pose.position.x = position_[0];
    pose.position.y = position_[1];
    pose.position.z = position_[2];
    pose.orientation.w = rotation_.w();
    pose.orientation.x = rotation_.x();
    pose.orientation.y = rotation_.y();
    pose.orientation.z = rotation_.z();
    return pose;
  }
  
  /// Returns a conversion of this pose object into a geometry_msgs::Transform.
  /// @return The converted geometry_msgs::Transform message
  inline geometry_msgs::Transform toTransformMessage(void)
  {
    geometry_msgs::Transform transform;
    transform.translation.x = position_[0];
    transform.translation.y = position_[1];
    transform.translation.z = position_[2];
    transform.rotation.w = rotation_.w();
    transform.rotation.x = rotation_.x();
    transform.rotation.y = rotation_.y();
    transform.rotation.z = rotation_.z();
    return transform;
  }
  
  /// Operator to check if two poses are equivalent.
  /// @param[in] pose The pose that is checked for equivalency against *this
  /// @return Bool defining if input and *this pose are equivalent
  inline bool operator==(const Pose& pose)
  { 
    return position_.isApprox(pose.position_) && rotation_.isApprox(pose.rotation_);
  }

  /// Operator to check if two poses are NOT equivalent.
  /// @param[in] pose The pose that is checked for non-equivalency against *this
  /// @return Bool defining if input and *this pose are non-equivalent
  inline bool operator!=(const Pose& pose)
  {
    return !position_.isApprox(pose.position_) || !rotation_.isApprox(pose.rotation_);
  }

  /// Returns inverse of pose.
  /// @return The inverse of *this pose
  inline Pose operator~(void) const 
  { 
    return Pose((rotation_.conjugate())._transformVector(-position_), rotation_.conjugate());
  }
  
  /// Transforms this pose according to an input geometry_msgs::Transform.
  /// @param[in] transform The input transformation msg
  /// @return The transformed pose
  inline Pose transform(const geometry_msgs::Transform& transform) const
  {
    Eigen::Vector3d position(position_ + Eigen::Vector3d(transform.translation.x,
                                           transform.translation.y,
                                           transform.translation.z));
    Eigen::Quaterniond rotation(rotation_ * Eigen::Quaterniond(transform.rotation.w,
                                                 transform.rotation.x,
                                                 transform.rotation.y,
                                                 transform.rotation.z));
    return Pose(position, rotation);
  }
  
  /// Transforms this pose according to an input transformation matrix constructed from DH matrices.
  /// @param[in] transform The input transformation matrix
  /// @return The transformed pose
  inline Pose transform(const Eigen::Matrix4d& transform) const
  {
    Pose return_pose;
    // Position
    Eigen::Vector4d result(position_[0], position_[1], position_[2], 1);
    result = transform * result;
    return_pose.position_ = Eigen::Vector3d(result[0], result[1], result[2]);
    // Orientation
    Eigen::Matrix3d rotation_matrix = transform.block<3, 3>(0, 0);
    return_pose.rotation_ = (Eigen::Quaterniond(rotation_matrix) * rotation_).normalized();
    return return_pose;
  }
  
  /// Transforms an input vector into the reference frame of this pose.
  /// @param[in] vec The input vector to be transformed into this pose's reference frame
  /// @return The transformed vector
  inline Eigen::Vector3d transformVector(const Eigen::Vector3d& vec) const 
  { 
    return position_ + rotation_._transformVector(vec);
  };
  
  /// Transforms an input vector from the reference frame of this pose.
  /// @param[in] vec The input vector to be transformed from this pose's reference frame
  /// @return The inversly transformed vector
  inline Eigen::Vector3d inverseTransformVector(const Eigen::Vector3d& vec) const 
  { 
    return (~*this).transformVector(vec);
  };
  
  /// Adds input pose to *this pose.
  /// @param[in] pose The pose to add from *this pose
  /// @return The combination of *this pose and input pose
  inline Pose addPose(const Pose& pose) 
  {
    Pose return_pose = (*this);
    return_pose.position_ = this->transformVector(pose.position_);
    return_pose.rotation_ *= pose.rotation_;
    return return_pose;
  }
  
  /// Removes input pose from *this pose.
  /// @param[in] pose The pose to remove from *this pose
  /// @return The resultant pose after removing input pose from *this pose
  inline Pose removePose (const Pose& pose)
  { 
    Pose return_pose = (*this);
    return_pose.position_ = this->transformVector(-pose.position_);
    return_pose.rotation_ *= pose.rotation_.inverse();
    return return_pose;
  };
  
  /// Generates interpolation from this pose to target pose using control input between zero and one.
  /// @param[in] control_input A value between 0.0 and 1.0 which defines the progress of interpolation
  /// @param[in] target_pose The target pose to which interpolation will return with control input of one
  /// @return The resultant interpolated pose
  inline Pose interpolate (const double& control_input, const Pose& target_pose)
  { 
    Eigen::Vector3d position = control_input * target_pose.position_ + (1.0 - control_input) * (*this).position_;
    Eigen::Quaterniond rotation = (*this).rotation_.slerp(control_input, target_pose.rotation_);
    return Pose(position, rotation);
  };
  
  /// Returns pose with position and rotation elements set to identity values.
  /// @return The Identity Pose
  inline static Pose Identity(void) 
  { 
    return Pose(Eigen::Vector3d::Zero(), Eigen::Quaterniond::Identity()); 
  }
  
  /// Returns pose with position and rotation elements all set to undefined values.
  /// @return The Undefined Pose
  inline static Pose Undefined(void) 
  { 
    return Pose(UNDEFINED_POSITION, UNDEFINED_ROTATION);
  }
  
  Eigen::Vector3d position_;     ///< The position element of the pose class
  Eigen::Quaterniond rotation_;  ///< The rotation element of the pose class

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SYROPOD_HIGHLEVEL_CONTROLLER_POSE_H
