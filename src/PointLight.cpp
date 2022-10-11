#include "PointLight.h"

void PointLight::direction(
    const Eigen::Vector3d &q, Eigen::Vector3d &d, double &max_t) const
{
  d = this->p - q;    // the direction toward the light is from the query point q to the light point p
  max_t = d.norm();   // the max length of the light is the distince between q and p
  d = d.normalized(); // normalize the direction vector
}
