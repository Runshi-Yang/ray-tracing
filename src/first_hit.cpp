#include "first_hit.h"

bool first_hit(
    const Ray &ray,
    const double min_t,
    const std::vector<std::shared_ptr<Object>> &objects,
    int &hit_id,
    double &t,
    Eigen::Vector3d &n)
{
  bool hit = false;
  double closest_hit = std::numeric_limits<int>::max(); // The closest hit found so far
  double hit_t;                                         // The hit t value obtained from intersect
  Eigen::Vector3d hit_n;                                // The hit normal value obtained from intersect

  for (int i = 0; i < objects.size(); i++) // loop through all the objects in the scene
  {
    if (objects[i]->intersect(ray, min_t, hit_t, hit_n))
    {
      if (hit_t < closest_hit)
      {
        // Update new closest hit
        hit_id = i;
        t = hit_t;
        n = hit_n;
        closest_hit = hit_t;
        hit = true;
      }
    }
  }

  return hit;
}
