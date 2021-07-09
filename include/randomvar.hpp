#pragma once
// represents random variable
#include <external.hpp>

namespace randomvar {

/**
  \brief Random variable as shown in Biagini and Campanino 2016, p. 4
*/
template <class InVal, class OutVal, class DistVal, class RVar>
struct RandomVar {
  bool max(const RVar &rvar, const OutVal &o_other, OutVal &out) const {
    return false;
  } // the v operator
  bool min(const RVar &rvar, const OutVal &o_other, OutVal &out) const {
    return false;
  } // ^ operator
  bool is_in_domain(const RVar &rvar, const InVal &in_val) const {
    return false;
  }
  bool is_in_codomain(const RVar &rvar, const OutVal &oval) const {
    return false;
  }
  bool outcome(const RVar &rvar, const InVal &in_val, OutVal &out) const {
    return false;
  }
};

} // namespace randomvar
