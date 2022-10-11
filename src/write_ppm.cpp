#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
    const std::string &filename,
    const std::vector<unsigned char> &data,
    const int width,
    const int height,
    const int num_channels)
{
  assert(
      (num_channels == 3 || num_channels == 1) &&
      ".ppm only supports RGB or grayscale images");
  /*
   * My implementation is based on the explanation from the following websites:
   * https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html
   * http://netpbm.sourceforge.net/doc/ppm.html
   */

  std::ofstream ppm_file(filename);

  if (!ppm_file.is_open()) // return false when file cannot be opened
  {
    perror("Can not open ppm file");
    return false;
  }

  ppm_file << "P3" << std::endl;                   // use the text-based .ppm formats
  ppm_file << width << " " << height << std::endl; // Input the number of columns and the number of rows in the image
  ppm_file << 255 << std::endl;                    // Maximum color value

  for (int i = 0; i < width * height * num_channels; i++)
  {
    if (num_channels == 3)
    {
      ppm_file << (unsigned int)data[i];
    }
    else // num_channels == 1, repeat channel value 3 times
    {
      ppm_file << (unsigned int)data[i] << " " << (unsigned int)data[i] << " " << (unsigned int)data[i];
    }

    if ((i + 1) % (num_channels * width) == 0)
    {
      ppm_file << std::endl; // Change the line when reach the right boundary of a picture
    }
    else if ((i + 1) % num_channels == 0)
    {
      ppm_file << "  "; // Add two whitespaces between two pixels
    }
    else
    {
      ppm_file << " "; // Add a whitespace between two channel values
    }
  }

  ppm_file.close();
  return true;
}
