#include "rt.h"

#include <cstdint>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>


namespace ftie {
  namespace rt {
    std::vector<uint8_t> encrypt(
      std::vector<uint8_t> plainbytes, std::vector<uint8_t> keystream
    ) {
      int n = plainbytes.size();
      int n_k = keystream.size();
      std::vector<uint8_t> cipherbytes(n * 2);
      std::random_device generateRandom;

      uint16_t n_matrix = uint32_t(std::ceil(std::sqrt((plainbytes.size() * 2) / 3.0)));
      size_t limit = n_matrix * 3;
      std::stringstream ss;
      ss << "/home/hafizhme/ftie-" << "random" << ".log";
      std::ofstream fout(ss.str());
      ss.clear();
      size_t token = 0;

      for (uint32_t i = 0; i < n; i ++) {
        uint8_t random = generateRandom();
        cipherbytes[i * 2] = keystream[i % n_k] + 2 * plainbytes[i] +  random;
        cipherbytes[i * 2 + 1] = 2 * keystream[i % n_k] + plainbytes[i] + random;

        if (token % limit == 0)
          fout << '\n';
        fout << std::setw(3) << int(random);
        fout << " ";
        token += 1;

        if (token % limit == 0)
          fout << '\n';
        fout << "   ";
        fout << " ";
        token += 1;
      }
      fout << '\n' << '\n';
      fout.close();

      return cipherbytes;
    }

    std::vector<uint8_t> decrypt(
      std::vector<uint8_t> cipherbytes, std::vector<uint8_t> keystream
    ) {
      int n = cipherbytes.size() / 2;
      int n_k = keystream.size();
      std::vector<uint8_t> plainbytes(n);
      for (uint32_t i = 0; i < n; i ++) {
        uint8_t a = cipherbytes[i * 2] - keystream[i % n_k];
        uint8_t b = cipherbytes[i * 2 + 1] - 2 * keystream[i % n_k];
        plainbytes[i] = a - b;
      }

      return plainbytes;
    }
  }
}
