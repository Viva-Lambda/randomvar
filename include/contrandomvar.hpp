#pragma once
// represents event
#include <external.hpp>
#include <randomvar.hpp>

using namespace randomvar;

namespace randomvar {

template <class InVal, class OutVal, class DistVal, class RVar>
struct ContRandomVar : RandomVar<InVal, OutVal, DistVal, RVar> {

  /**\brief Probability density function of a continuous random variable*/
  bool pdf(const RVar &var, OutVal x, DistVal &out) const { return false; }

  /**\brief cumulative density function of a continuous random variable*/
  bool cdf(const RVar &var, OutVal x, DistVal &out) const { return false; }

  /**\brief mean value of the random variable */
  bool mean(const RVar &var, OutVal &out) const { return false; }

  /**\brief mode of the random variable */
  bool mode(const RVar &var, OutVal &out) const { return false; }

  /**\brief variance of the random variable */
  bool variance(const RVar &var, OutVal &out) const { return false; }
};

} // namespace randomvar
