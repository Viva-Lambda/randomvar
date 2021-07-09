// test file for quaternion
#include <catrandomvar.hpp>
#include <contrandomvar.hpp>
#include <ctest.h>
#include <event.hpp>
#include <gaussianvar.hpp>
#include <randomvar.hpp>
#include <uniformvar.hpp>

CTEST(suite, test_hello) {
  std::function<float(unsigned int)> fn = [](unsigned int a) {
    return static_cast<float>(a + 2);
  };
  unsigned int minv = 4;
  unsigned int maxv = 10;
  UniformVar<unsigned int, float> uvar("first uvar", fn, minv, maxv);
}
