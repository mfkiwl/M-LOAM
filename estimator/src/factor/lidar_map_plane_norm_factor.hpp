#include <ceres/ceres.h>
#include <ceres/rotation.h>

#include <eigen3/Eigen/Dense>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl_conversions/pcl_conversions.h>

// calculate distrance from point to plane (using normal)
struct LidarMapPlaneNormFactor
{
	LidarMapPlaneNormFactor(const Eigen::Vector3d &point, const Eigen::Vector4d &coeff, const Eigen::Matrix3d &cov_matrix = Eigen::Matrix3f::Identity())
		: point_(point), coeff_(coeff), cov_matrix_(cov_matrix){}

	template <typename T>
	bool operator()(const T *param, T *residual) const
	{
		Eigen::Quaternion<T> q_w_curr(param[6], param[3], param[4], param[5]);
		Eigen::Matrix<T, 3, 1> t_w_curr(param[0], param[1], param[2]);

		Eigen::Matrix<T, 3, 1> w(T(coeff_(0)), T(coeff_(1)), T(coeff_(2)));
		Eigen::Matrix<T, 3, 1> cp(T(point_(0)), T(point_(1)), T(point_(2)));
		T d = T(coeff_(3));
		T a = w.dot(q_w_curr * cp + t_w_curr) + d;
		// T r = w.dot(q_w_curr * cp + t_w_curr) + d;
		T r = (a * w.transpose()) * cov_matrix_.inverse().cast<T>() * (a * w);
		residual[0] = T(sqrt(abs(r))); // TODO: should be always positive?
		return true;
	}

	static ceres::CostFunction *Create(const Eigen::Vector3d &point, const Eigen::Vector4d &coeff, const Eigen::Matrix3d &cov_matrix)
	{
		return (new ceres::AutoDiffCostFunction<
				LidarMapPlaneNormFactor, 1, 7>(new LidarMapPlaneNormFactor(point, coeff, cov_matrix)));
	}

	Eigen::Vector3d point_;
	Eigen::Vector4d coeff_;
	Eigen::Matrix3d cov_matrix_;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
