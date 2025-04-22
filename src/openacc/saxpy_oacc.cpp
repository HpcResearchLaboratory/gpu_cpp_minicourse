#include <cassert>
#include <iostream>

#include "device_vector.hpp"

device_vector<float> saxpy(const device_vector<float>& x,
                           const device_vector<float>& y, float a) {
  assert(x.size() == y.size());

  device_vector<float> z(x.size());

#pragma acc parallel loop
  for (auto i = 0ull; i < y.size(); ++i) z[i] = a * x[i] + y[i];
  return z;
}

int main() {
  constexpr std::size_t N = 1 << 24;
  const float a = 1.0F;

  const device_vector<float> x(N, 2.0F);
  const device_vector<float> y(N, 3.0F);

  auto z = saxpy(x, y, a);
  float sum = 0;
#pragma acc parallel loop reduction(+ : sum) copy(sum)
  for (auto i = 0ull; i < z.size(); ++i) sum += z[i];

  std::cout << "Final result = " << sum << std::endl;
  return 0;
}
