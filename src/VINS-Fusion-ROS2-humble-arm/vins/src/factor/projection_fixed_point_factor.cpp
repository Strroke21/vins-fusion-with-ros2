#include "projection_fixed_point_factor.h"

Eigen::Matrix2d ProjectionFixedPointFactor::sqrt_info;

ProjectionFixedPointFactor::ProjectionFixedPointFactor(const Eigen::Vector3d &_pts_w, const Eigen::Vector3d &_pts_j)
    : pts_w(_pts_w), pts_j(_pts_j)
{
}

bool ProjectionFixedPointFactor::Evaluate(double const *const *parameters, double *residuals, double **jacobians) const
{
    Eigen::Vector3d Pj(parameters[0][0], parameters[0][1], parameters[0][2]);
    Eigen::Quaterniond Qj(parameters[0][6], parameters[0][3], parameters[0][4], parameters[0][5]);

    Eigen::Vector3d tic(parameters[1][0], parameters[1][1], parameters[1][2]);
    Eigen::Quaterniond qic(parameters[1][6], parameters[1][3], parameters[1][4], parameters[1][5]);

    Eigen::Vector3d pts_imu_j = Qj.inverse() * (pts_w - Pj);
    Eigen::Vector3d pts_camera_j = qic.inverse() * (pts_imu_j - tic);

    Eigen::Map<Eigen::Vector2d> residual(residuals);
    double dep_j = pts_camera_j.z();
    residual = (pts_camera_j / dep_j).head<2>() - pts_j.head<2>();
    residual = sqrt_info * residual;

    if (jacobians)
    {
        Eigen::Matrix3d Rj = Qj.toRotationMatrix();
        Eigen::Matrix3d ric = qic.toRotationMatrix();

        Eigen::Matrix<double, 2, 3> reduce;
        reduce << 1. / dep_j, 0, -pts_camera_j(0) / (dep_j * dep_j),
            0, 1. / dep_j, -pts_camera_j(1) / (dep_j * dep_j);
        reduce = sqrt_info * reduce;

        if (jacobians[0])
        {
            // Same structure as ProjectionTwoFrameOneCamFactor's jaco_j: pts_w
            // is a constant here just as pts_w (=Qi*pts_imu_i+Pi) was already
            // being treated as independent of pose_j there.
            Eigen::Map<Eigen::Matrix<double, 2, 7, Eigen::RowMajor>> jacobian_pose_j(jacobians[0]);

            Eigen::Matrix<double, 3, 6> jaco_j;
            jaco_j.leftCols<3>() = ric.transpose() * -Rj.transpose();
            jaco_j.rightCols<3>() = ric.transpose() * Utility::skewSymmetric(pts_imu_j);

            jacobian_pose_j.leftCols<6>() = reduce * jaco_j;
            jacobian_pose_j.rightCols<1>().setZero();
        }

        if (jacobians[1])
        {
            // Simpler than ProjectionTwoFrameOneCamFactor's jaco_ex: the
            // extrinsic only enters once here (pts_camera_j = qic^-1(pts_imu_j
            // - tic)), not on both the i and j sides, since there is no frame i.
            Eigen::Map<Eigen::Matrix<double, 2, 7, Eigen::RowMajor>> jacobian_ex_pose(jacobians[1]);

            Eigen::Matrix<double, 3, 6> jaco_ex;
            jaco_ex.leftCols<3>() = -ric.transpose();
            jaco_ex.rightCols<3>() = Utility::skewSymmetric(pts_camera_j);

            jacobian_ex_pose.leftCols<6>() = reduce * jaco_ex;
            jacobian_ex_pose.rightCols<1>().setZero();
        }
    }

    return true;
}
