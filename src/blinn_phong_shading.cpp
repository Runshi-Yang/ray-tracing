#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

#define AMBIENT_INTENSITY 0.1
#define FUDGE_FACTOR 1e-6

Eigen::Vector3d blinn_phong_shading(
    const Ray &ray,
    const int &hit_id,
    const double &t,
    const Eigen::Vector3d &n,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights)

{
  // Diffuse coeffient for the list of objects in the scene
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  // Specular coeffient for the list of objects in the scene
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  // Ambient coeffient for the list of objects in the scene
  Eigen::Vector3d ka = objects[hit_id]->material->ka;
  // Phong exponent
  double phong_exponent = objects[hit_id]->material->phong_exponent;

  // Initialize the all black scene
  Eigen::Vector3d result(0, 0, 0);

  // Add the Ambient light to all the objects in the scene
  result += AMBIENT_INTENSITY * ka;

  // Viewing ray
  Eigen::Vector3d e = ray.origin;    // the eye point in the 3D SPACE
  Eigen::Vector3d d = ray.direction; // the direction from the eye point to the query point

  // Shadow ray
  Ray shadow_ray;
  Eigen::Vector3d q = e + t * d; // the query point
  Eigen::Vector3d l;             // the direction from the query point to the light
  shadow_ray.origin = q;         // the origin of the shadow ray is the query point
  double max_t;                  // the following variables are used to determine whether the shadow ray hits an object
  int shadow_ray_hit_id;
  double shadow_ray_t;
  Eigen::Vector3d shadow_ray_n;

  /*
   * Iterate through every light and calculate the lambertian and specular lights
   *  and use them to set the result color for objects.
   */
  for (int i = 0; i < lights.size(); i++)
  {
    // Find the normalized direction from q towards light (l), and parametric distance from q along l to light (max_t)
    lights[i]->direction(q, l, max_t);
    shadow_ray.direction = l;

    // If the ray from the query point to the light does not hit any object, then the light will change the color of the query point
    if (!first_hit(shadow_ray, FUDGE_FACTOR, objects, shadow_ray_hit_id, shadow_ray_t, shadow_ray_n) || shadow_ray_t >= max_t)
    {
      // Add the diffuse component (Lambertian shading) to the pixel color
      Eigen::Vector3d lambertian = (kd.array() * lights[i]->I.array()).matrix() * std::fmax(0.0, n.dot(l)); // component-wise multiplication
      result += lambertian;
      // Add the specular component (Blinn-Phong shading) to the pixel color
      Eigen::Vector3d h = (-d.normalized() + l).normalized(); // notice that d is not necessarily a unit-length direction vector
      Eigen::Vector3d specular = (ks.array() * lights[i]->I.array()).matrix() * std::pow(std::fmax(0.0, n.dot(h)), phong_exponent);
      result += specular;
    }
  }
  // since the rgb color is clipped in main function, we can return it directly.
  return result;
}
