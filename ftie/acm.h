#ifndef ACM_H
#define ACM_H

#include "png++/png.hpp"

#include <cstdint>
#include <vector>


namespace ftie {
  namespace acm {
    png::image<png::rgb_pixel> encrypt(
      uint16_t a, uint16_t b, uint16_t n,
      png::image<png::rgb_pixel> plainimage
    );
    png::image<png::rgb_pixel> decrypt(
      uint16_t a, uint16_t b, uint16_t n,
      png::image<png::rgb_pixel> cipherimage
    );
  }
}

#endif
