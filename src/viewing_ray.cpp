#include "viewing_ray.h"

void viewing_ray(
    const Camera &camera,
    const int i,
    const int j,
    const int width,
    const int height,
    Ray &ray)
{
  // Find the origin of the ray in world space
  ray.origin = camera.e;

  // Find the u, v, w components of the ray in camera space
  double u, v, w;
  u = ((j + 0.5) * camera.width / width) - (camera.width / 2.0);
  v = (camera.height / 2.0) - ((i + 0.5) * camera.height / height);
  w = -1 * camera.d;

  // Place them in a vector to represent the direction of the ray in camera space
  Eigen::Vector3d camera_ray_direction(u, v, w);

  // Place the basis of the camera space to a matrix to perfrom the transformation from camera space to world space
  Eigen::Matrix3d camera_to_world;
  camera_to_world << camera.u, camera.v, camera.w;

  // Find the ray direction in world space
  ray.direction = camera_to_world * camera_ray_direction;
}
