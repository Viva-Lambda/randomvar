#pragma once
// represents event
#include <external.hpp>
#include <randomvar.hpp>

using namespace randomvar;

namespace randomvar {
template <class InVal, class DistVal, class RVar>
struct Event : RandomVar<InVal, bool, DistVal, RVar> {
  /**
    An event interface from Biagini Campanino 2016, p. 5
   */
};

} // namespace randomvar
