#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  bool intersect = false;

  // Set up some vectors to represent the plane and line
  Eigen::Vector3d p = this->point; // Point on plane
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d v = ray.direction;

  double denominator = v.dot(this->normal);
  /*
   * If the normal of plane dot product with the direction of the ray equals to 0,
   * then the line is parallel to the plane or in the plane.
   * In this case, return false.
   */
  if (denominator != 0)
  {
    /*
    Else, find t according to the formula we learned in the lecture.
    */
    double numerator = this->normal.dot(p - e);
    t = numerator / denominator;
    if (t >= min_t) // the ray intersect the plane only when t is greater than min_t.
    {
      n = this->normal;
      intersect = true;
    }
  }
  return intersect;
}
