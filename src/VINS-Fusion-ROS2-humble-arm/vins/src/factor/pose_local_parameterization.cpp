/*******************************************************
 * Copyright (C) 2019, Aerial Robotics Group, Hong Kong University of Science and Technology
 * 
 * This file is part of VINS.
 * 
 * Licensed under the GNU General Public License v3.0;
 * you may not use this file except in compliance with the License.
 *******************************************************/

#include "pose_local_parameterization.h"

bool PoseLocalParameterization::Plus(const double *x, const double *delta, double *x_plus_delta) const
{
    Eigen::Map<const Eigen::Vector3d> _p(x);
    Eigen::Map<const Eigen::Quaterniond> _q(x + 3);

    Eigen::Map<const Eigen::Vector3d> dp(delta);

    Eigen::Quaterniond dq = Utility::deltaQ(Eigen::Map<const Eigen::Vector3d>(delta + 3));

    Eigen::Map<Eigen::Vector3d> p(x_plus_delta);
    Eigen::Map<Eigen::Quaterniond> q(x_plus_delta + 3);

    p = _p + dp;
    q = (_q * dq).normalized();

    return true;
}
bool PoseLocalParameterization::PlusJacobian(const double *x, double *jacobian) const
{
    Eigen::Map<Eigen::Matrix<double, 7, 6, Eigen::RowMajor>> j(jacobian);
    j.topRows<6>().setIdentity();
    j.bottomRows<1>().setZero();

    return true;
}

bool PoseLocalParameterization::Minus(const double *y, const double *x, double *y_minus_x) const
{
    Eigen::Map<const Eigen::Vector3d> p_y(y);
    Eigen::Map<const Eigen::Quaterniond> q_y(y + 3);
    Eigen::Map<const Eigen::Vector3d> p_x(x);
    Eigen::Map<const Eigen::Quaterniond> q_x(x + 3);

    Eigen::Map<Eigen::Vector3d> dp(y_minus_x);
    dp = p_y - p_x;

    // Inverse of the same small-angle approximation Plus()/Utility::deltaQ
    // use: dq = q_x^{-1} * q_y ~= [1, dtheta/2] for small dtheta, so
    // dtheta = 2 * dq.vec(). Only exercised by Ceres APIs this codebase
    // doesn't call (Problem::Evaluate with local Jacobians, Covariance) --
    // ceres::Solve() itself only needs Plus/PlusJacobian -- so this being an
    // approximation rather than an exact inverse doesn't affect the solve.
    Eigen::Quaterniond dq = q_x.inverse() * q_y;
    Eigen::Map<Eigen::Vector3d> dtheta(y_minus_x + 3);
    dtheta = 2.0 * dq.vec();

    return true;
}

bool PoseLocalParameterization::MinusJacobian(const double *x, double *jacobian) const
{
    Eigen::Map<Eigen::Matrix<double, 6, 7, Eigen::RowMajor>> j(jacobian);
    j.setZero();
    j.block<3, 3>(0, 0).setIdentity();
    j.block<3, 3>(3, 3) = 2.0 * Eigen::Matrix3d::Identity();

    return true;
}
