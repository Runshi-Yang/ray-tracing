#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  // Find the three corners of the triangle
  Eigen::Vector3d x1 = std::get<0>(this->corners);
  Eigen::Vector3d x2 = std::get<1>(this->corners);
  Eigen::Vector3d x3 = std::get<2>(this->corners);

  // Find the two sides of the triangle with x1 as the vertex,
  // then we know that if a point in the triangle satisfies:
  // p = a * t1 + b * t2 + x1
  // where a, b >= 0 and a + b <= 1.
  Eigen::Vector3d t1 = x2 - x1;
  Eigen::Vector3d t2 = x3 - x1;

  // Use the formula we learned in tutorial, we know that M *[a, b, t] = 0 gives us the point of the intersection.
  Eigen::Matrix3d M;
  M << t1, t2, -1 * ray.direction;

  /*
   * The matrix m is not invertible, so there is no solution, which means there is no intersection.
   */
  if (M.determinant() == 0)
  {
    return false;
  }

  /*
   * The matrix m is invertible, so there is solution, which means there might be intersection.
   */
  else
  {
    double a, b;
    Eigen::Vector3d solution = M.inverse() * (ray.origin - x1);
    a = solution[0];
    b = solution[1];
    t = solution[2];
    // if a, b satisfies the condition and t >= min_t, then the ray intersects with the triangle.
    if (a >= 0 & b >= 0 & a + b <= 1 & t >= min_t)
    {
      n = t1.cross(t2).normalized();
      return true;
    }
    // else, the ray does not intersect with the triangle.
    else
    {
      return false;
    }
  }
}
