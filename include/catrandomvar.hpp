#pragma once

// represents random variable
#include <external.hpp>
#include <randomvar.hpp>

using namespace randomvar;

namespace randomvar {

template <class InVal, class OutVal> struct CatRVar {
  std::string id;
  std::function<OutVal(InVal)> fn;
  std::vector<InVal> data;
  CatRVar() {}
  CatRVar(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
          const std::vector<InVal> &vdata)
      : id(varid), fn(_fn), data(vdata) {}
};

template <class InVal, class OutVal, class DistVal, class RVar>
struct CatRandomVar : RandomVar<InVal, OutVal, DistVal, RVar> {

  /**\brief Probability mass function of a categorical random variable*/
  bool pmf(const RVar &var, OutVal x, DistVal &out) const { return false; }
  bool mode(const RVar &var, DistVal &out) const { return false; }
};

template <class InVal, class OutVal, class DistVal>
struct CatRVarDist : CatRVar<InVal, OutVal> {
  std::function<bool(OutVal, DistVal &)> dist;
  CatRVarDist() : CatRVar<InVal, OutVal>() {}
  CatRVarDist(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
              const std::vector<InVal> &vdata,
              const std::function<bool(OutVal, DistVal &)> &d)
      : CatRVar<InVal, OutVal>(varid, _fn, vdata), dist(d) {}
};

} // namespace randomvar
