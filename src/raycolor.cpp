#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

#define FUDGE 1e-4
#define MAX_DEPTH 8

bool raycolor(
    const Ray &ray,
    const double min_t,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights,
    const int num_recursive_calls,
    Eigen::Vector3d &rgb)
{
  bool hit = false;
  // the recursive call ends when the light reflects MAX_DEPTH times
  if (num_recursive_calls < MAX_DEPTH)
  {
    rgb = Eigen::Vector3d(0, 0, 0);

    // Variables used to determine whether the viewing ray hits an object
    Eigen::Vector3d n;
    double t;
    int hit_id;
    // If the viewing ray hits an object
    if (first_hit(ray, min_t, objects, hit_id, t, n))
    {
      // get the color of the pixel that shoot out the viewing ray using the blinn_phong_shading function
      rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

      // reflected ray
      Ray reflected_ray;
      reflected_ray.origin = ray.origin + t * ray.direction; // the point of the reflection is the point on the object
      reflected_ray.direction = reflect(ray.direction, n);   // reflect direction

      // add the reflected color to our original pixel color recursively.
      Eigen::Vector3d reflect_rgb;
      if (raycolor(reflected_ray, FUDGE, objects, lights, num_recursive_calls + 1, reflect_rgb))
      {
        // Then we can update the rgb value. Component-wise multiplication
        rgb += (objects[hit_id]->material->km.array() * reflect_rgb.array()).matrix();
      }
      hit = true;
    }
  }
  return hit;
}
