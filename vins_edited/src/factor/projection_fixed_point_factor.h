/*******************************************************
 * Anchors a single sliding-window pose against a fixed 3D point recovered
 * from the short-horizon local relocalization bank (see Estimator's
 * localMapBank / relocalizeAgainstLocalMap). Unlike ProjectionTwoFrameOneCamFactor,
 * the 3D point here is a CONSTANT -- captured from a healthy keyframe and
 * PnP-RANSAC-verified against the current frame -- not a co-optimized
 * inverse-depth parameter. Only fires when the visual feature gate is closed
 * and enough RANSAC inliers were found; see Estimator::optimization().
 *
 * Deliberately added only in the live-solve section of optimization(), never
 * in the MARGIN_OLD reconstruction loop -- so it affects the current cycle's
 * solve only and is never carried into the marginalization prior.
 *******************************************************/

#pragma once

#include <rcpputils/asserts.hpp>
#include <ceres/ceres.h>
#include <Eigen/Dense>
#include "../utility/utility.h"
#include "../utility/tic_toc.h"
#include "../estimator/parameters.h"

class ProjectionFixedPointFactor : public ceres::SizedCostFunction<2, 7, 7>
{
  public:
    ProjectionFixedPointFactor(const Eigen::Vector3d &_pts_w, const Eigen::Vector3d &_pts_j);
    virtual bool Evaluate(double const *const *parameters, double *residuals, double **jacobians) const;

    Eigen::Vector3d pts_w; // fixed 3D point, world frame, from the bank
    Eigen::Vector3d pts_j; // observed normalized ray in the current frame
    static Eigen::Matrix2d sqrt_info;
};
