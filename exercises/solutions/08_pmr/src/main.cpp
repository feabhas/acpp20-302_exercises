// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <array>
#include <iostream>
#include <memory_resource>
#include <vector>
#include <numeric>

using std::pmr::monotonic_buffer_resource;

class trace_mbr : public monotonic_buffer_resource
{
public:
  using monotonic_buffer_resource::monotonic_buffer_resource;
  [[nodiscard]] void* do_allocate(size_t bytes, [[maybe_unused]] size_t alignment) override {
    std::cout << "allocate " << bytes << " align " << alignment << '\n';
    auto ptr = monotonic_buffer_resource::do_allocate(bytes, alignment);
    std::cout << " => " << ptr << '\n';
	  return ptr;
  }

  void do_deallocate(void* ptr, std::size_t bytes, [[maybe_unused]] size_t alignment) noexcept override {
    std::cout << "de-allocate " << bytes << " align " << alignment
              << " <= " << ptr << '\n';
    monotonic_buffer_resource::do_deallocate(ptr, bytes, alignment);
	}
};

static std::array<int, 10> buffer{};

int adder()
{
  std::pmr::monotonic_buffer_resource pmr_buffer(std::data(buffer), std::size(buffer)*sizeof(int));
  // trace_mbr pmr_buffer(std::data(buffer), std::size(buffer)*sizeof(int));
  std::pmr::vector<int> vec(&pmr_buffer);
  // vec.reserve(10);

  std::cout << "Enter integers one per line?" << '\n';
  int value {};
  while (std::cin >> value && value > 0) {
    std::cout << "size " << vec.size() << " capacity " << vec.capacity() << '\n';
    vec.emplace_back(value);
  }
  return std::accumulate(std::begin(vec), std::end(vec), 0);
}

int main()
{
  std::pmr::set_default_resource(std::pmr::null_memory_resource());
  int sum = adder();
  std::cout << "sum A " << sum << '\n';
  sum = adder();
  std::cout << "sum B " << sum << '\n';
}
