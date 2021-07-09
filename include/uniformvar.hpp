#ifndef UNIFORMVAR_HPP
#define UNIFORMVAR_HPP

#include <contrandomvar.hpp>
#include <external.hpp>
#include <random>

using namespace randomvar;

namespace randomvar {

template <class InVal, class OutVal> struct UniformVar {
  std::string id;
  std::function<OutVal(InVal)> fn;
  InVal imin;
  InVal imax;

  UniformVar() {}
  UniformVar(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
             const InVal &_inmin, const InVal &_inmax)
      : id(varid), fn(_fn), imin(_inmin), imax(_inmax) {}

  OutVal upper() const {
    auto omin = fn(imin);
    auto omax = fn(imax);
    if (omin > omax)
      return omin;
    return omax;
  }
  OutVal lower() const {
    auto omin = fn(imin);
    auto omax = fn(imax);
    if (omin < omax)
      return omin;
    return omax;
  }
};

template <class InVal, class OutVal, class DistVal>
struct ContRandomVar<InVal, OutVal, DistVal, UniformVar<InVal, OutVal>> {

  bool max(const UniformVar<InVal, OutVal> &rvar, const OutVal &o_other,
           OutVal &out) const {
    OutVal ov = rvar.upper();
    out = ov > o_other ? ov : o_other;
    return true;
  } // namespace randomvar
  bool min(const UniformVar<InVal, OutVal> &rvar, const OutVal &o_other,
           OutVal &out) const {
    OutVal ov = rvar.lower();
    out = ov < o_other ? ov : o_other;
    return true;
  } // the v operator

  bool is_in_domain(const UniformVar<InVal, OutVal> &rvar,
                    const InVal &in_val) const {
    if (rvar.imin <= in_val && in_val <= rvar.imax)
      return true;
    return false;
  }
  bool is_in_codomain(const UniformVar<InVal, OutVal> &rvar,
                      const OutVal &oval) const {
    auto omin = rvar.lower();
    auto omax = rvar.upper();
    if (omin <= oval && oval <= omax)
      return true;
    return false;
  }
  bool outcome(const UniformVar<InVal, OutVal> &rvar, const InVal &in_val,
               OutVal &out) const {
    bool res = is_in_domain(rvar, in_val);
    if (res == false)
      return res;
    out = rvar.fn(in_val);
    return true;
  }
  /**
    From Biagini 2016, p. 42
    */
  bool pdf(const UniformVar<InVal, OutVal> &var, OutVal x, DistVal &out) const {
    OutVal o_max = var.upper();
    OutVal o_min = var.lower();
    // if is oval in codomain
    // 1 / (o_max - o_min)
    // else 0
    bool res = is_in_codomain(var, x);
    if (res == false) {
      out = static_cast<DistVal>(0);
      return true;
    } else {
      out = static_cast<DistVal>(1) / static_cast<DistVal>(o_max - o_min);
      return true;
    }
  }

  /**
    \brief cumulative density function of a continuous
    random variable
    Biagini 2016, p. 47
   */
  bool cdf(const UniformVar<InVal, OutVal> &var, OutVal x, DistVal &out) const {
    auto lv = var.lower();
    auto uv = var.upper();
    if (x <= lv) {
      out = static_cast<DistVal>(0);
      return true;
    }
    if (x >= uv) {
      out = static_cast<DistVal>(1);
      return true;
    }
    out = static_cast<DistVal>(x - lv) / static_cast<DistVal>(uv - lv);
    return true;
  }
  bool mode(const UniformVar<InVal, OutVal> &var, OutVal &out) const {
    auto lv = var.lower();
    auto uv = var.upper();
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<OutVal> distribution(lv, uv);
    out = distribution(generator);
    return true;
  }
  /**\brief variance of the random variable
     Biagini 2016, p. 47
  */
  bool mean(const UniformVar<InVal, OutVal> &var, OutVal &out) const {

    auto lv = var.lower();
    auto uv = var.upper();
    out = static_cast<OutVal>(lv + uv) / static_cast<OutVal>(2);
    return true;
  }

  /**\brief variance of the random variable
    Biagini 2016, p. 47
   */
  bool variance(const UniformVar<InVal, OutVal> &var, OutVal &out) const {

    auto lv = var.lower();
    auto uv = var.upper();
    out = (uv - lv) * (uv - lv) / static_cast<OutVal>(12);
    return true;
  }
};

} // namespace randomvar
// namespace randomvar
#endif
