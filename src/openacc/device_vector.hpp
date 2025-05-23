#include <cstddef>

template <typename T>
class device_vector {
 public:
  device_vector() = default;

  explicit device_vector(size_t size) {
    _size = size;
    _A = new T[_size];
#pragma acc enter data copyin(this) create(_A[0 : _size])
  }

  explicit device_vector(size_t size, const T &value) {
    _size = size;
    _A = new T[_size];
    for (int i = 0; i < _size; ++i) {
      _A[i] = value;
    }
#pragma acc enter data copyin(this, _A[0 : _size])
  }

  ~device_vector() {
#pragma acc exit data delete (this, _A[0 : _size])
    delete[] _A;
    _A = nullptr;
    _size = 0;
  }

  void update_host() {
#pragma acc update self(_A[0 : _size])
  }

  void update_device() {
#pragma acc update device(_A[0 : _size])
  }

#pragma acc routine seq
  inline T &operator[](size_t idx) { return _A[idx]; }

#pragma acc routine seq
  inline T &operator[](size_t idx) const { return _A[idx]; }

#pragma acc routine seq
  size_t size() const { return _size; }

 private:
  T *_A{nullptr};
  size_t _size{0};
};
