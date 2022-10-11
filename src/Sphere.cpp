#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = this->center;
  double r = this->radius;

  // Coefficients of equation A*t^2 + B*t + C = 0 (*)
  double A = d.dot(d);
  double B = 2.0 * d.dot(e - c);
  double C = (e - c).dot(e - c) - r * r;

  double discriminant = B * B - 4 * A * C; // Discriminant

  /*
   * There is no solution to equation (*), means the ray does not intersect with the sphere.
   */
  if (discriminant < 0)
  {
    return false;
  }
  /*
   * There is one solution to equation (*), means the ray is tangent to the sphere.
   */
  else if (discriminant == 0)
  {
    t = -B / (2 * A);
    if (t >= min_t)
    {
      n = ((e + t * d) - c) / r; // The normal points from the center of the sphere to the point of intersection.
      return true;
    }
  }
  /*
   * There are two solutions to equation (*), means the line of the ray pass through the sphere.
   */
  else
  {
    // Calculate the two solutions
    double t_plus = (-B + sqrt(discriminant)) / (2 * A);
    double t_minus = (-B - sqrt(discriminant)) / (2 * A);

    double t_small = fmin(t_plus, t_minus);
    double t_large = fmax(t_plus, t_minus);
    if (t_large < min_t)
    {
      // The sphere is behind the origin of the ray, so there is no intersection
      return false;
    }
    else
    {
      if (t_small >= min_t)
      { // The ray and the sphere have two points of intersection, take the closer one
        t = t_small;
      }
      else if (t_large >= min_t)
      { // The origin of the ray is in the sphere, so take the larger one
        t = t_large;
      }
      // Calculate the norm at the closest point of intersection
      n = ((e + t * d) - c) / r;
      return true;
    }
  }
}
