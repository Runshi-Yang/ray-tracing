#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d &in, const Eigen::Vector3d &n)
{
  Eigen::Vector3d r = in - 2.0 * (in.dot(n)) * n; // the direction of the reflected ray
  return r.normalized();                          // normalize r
}
