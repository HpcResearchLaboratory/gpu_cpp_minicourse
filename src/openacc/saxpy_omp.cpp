#include <omp.h>

#include <cassert>
#include <iostream>
#include <vector>

std::vector<float> saxpy(const std::vector<float>& x,
                         const std::vector<float>& y, float a) {
  assert(x.size() == y.size());
  std::vector<float> z(x.size());

#pragma omp parallel for
  for (size_t i = 0; i < x.size(); ++i) z[i] = a * x[i] + y[i];

  return z;
}

int main() {
  constexpr std::size_t N = 1 << 24;
  const float a = 2.0f;
  std::vector<float> x(N, 1.0f);
  std::vector<float> y(N, 2.0f);

  auto z = saxpy(x, y, a);

  float sum = 0.0f;
#pragma omp parallel for reduction(+ : sum)
  for (size_t i = 0; i < z.size(); ++i) sum += z[i];

  std::cout << sum << std::endl;
  return 0;
}
