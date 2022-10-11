#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
    const Eigen::Vector3d &q, Eigen::Vector3d &d, double &max_t) const
{
  d = (-this->d).normalized();                     // the direction toward the light is the opposite of the direction from light toward scene
  max_t = std::numeric_limits<double>::infinity(); // the direction light is from infinity far away
}
