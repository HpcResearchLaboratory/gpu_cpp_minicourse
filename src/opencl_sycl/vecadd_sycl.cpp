#include <sycl/sycl.hpp>

using namespace sycl;

auto vecadd(queue &q, const int *a, const int *b, int *sum, size_t size)
    -> void {
  range<1> num_items{size};
  auto e = q.parallel_for(
        num_items,
        [=](auto i) { sum[i] = a[i] + b[i]; }
   );
  e.wait();
}

auto main(int argc, char *argv[]) -> int {
  constexpr auto array_size = 10000;
  auto selector = gpu_selector_v;

  sycl::queue q(selector);

  int *a = malloc_shared<int>(array_size, q);
  int *b = malloc_shared<int>(array_size, q);
  int *sum = malloc_shared<int>(array_size, q);

  vecadd(q, a, b, sum, array_size);

  free(a, q);
  free(b, q);
  free(sum, q);
}
