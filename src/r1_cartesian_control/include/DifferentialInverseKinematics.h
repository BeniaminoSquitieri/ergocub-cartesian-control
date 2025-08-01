// SPDX-FileCopyrightText: 2025 Humanoid Sensing and Perception, Istituto Italiano di Tecnologia
// SPDX-License-Identifier: BSD-3-Clause

#ifndef DIFFERENTIAL_INVERSE_KINEMATICS_H
#define DIFFERENTIAL_INVERSE_KINEMATICS_H

#include <Eigen/Dense>
#include <optional>

/**
 * Abstract class representing the differential inverse kinematics of a kinematic chain.
 */
class DifferentialInverseKinematics
{
public:
    virtual ~DifferentialInverseKinematics() = default;

    /**
     * Evaluate the reference joints velocities that drive the robot end-effector towards the desired transform.
     * @return The reference velocities that realize the inverse kinematics in radian/s.
     * @warning This method should be called only after setting the current robot state via DifferentialInverseKinematics::set_robot_state()
     *          and the desired end-effector transform via DifferentialInverseKinematics::set_desired_ee_transform().
     */
    virtual std::optional<Eigen::VectorXd> eval_reference_velocities() = 0;

    /**
     * Set the current robot state.
     * @param joints The current joint configuration \f$ q \f$.
     * @param transform The current end-effector transformation.
     * @param jacobian The current end-effector Jacobian.
     */
    virtual void set_robot_state(
        const Eigen::Ref<const Eigen::VectorXd> &joints,
        const Eigen::Ref<const Eigen::VectorXd> &joints_vel,
        const Eigen::Transform<double, 3, Eigen::Affine> &transform,
        const Eigen::Ref<const Eigen::MatrixXd> &jacobian) = 0;

    /**
     * Set the desired root to end-effector transform.
     * @param transform The desired end-effector transformation.
     */
    virtual void set_desired_ee_transform(const Eigen::Transform<double, 3, Eigen::Affine> &transform) = 0;

    /**
     * Set the joints limits.
     * @param lower_limits The joint lower limits \f$q_{L}\f$.
     * @param upper_limits The joint upper limits \f$q_{U}\f$.
     * @param gains The joint limits gains \f$K_l\f$.
     */
    virtual void set_joint_limits(
        const Eigen::Ref<const Eigen::VectorXd> &lower_limits,
        const Eigen::Ref<const Eigen::VectorXd> &upper_limits,
        const Eigen::Ref<const Eigen::VectorXd> &gains) = 0;
};

#endif /* DIFFERENTIAL_INVERSE_KINEMATICS_H */
