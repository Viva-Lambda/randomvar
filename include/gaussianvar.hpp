#pragma once
#include <contrandomvar.hpp>
#include <external.hpp>

using namespace randomvar;

namespace randomvar {

template <class InVal, class OutVal, class DistVal> struct GaussianVar {
  std::string id;
  std::function<OutVal(InVal)> fn;
  InVal imax;
  InVal imin;
  OutVal mean_value;
  DistVal standard_dev;

  GaussianVar() {}
  GaussianVar(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
              const InVal &_inmin, const InVal &_inmax, OutVal m, DistVal sdev)
      : id(varid), fn(_fn), imin(_inmin), imax(_inmax), mean_value(m),
        standard_dev(sdev) {}

  GaussianVar(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
              const InVal &_inmin, const InVal &_inmax, OutVal m)
      : id(varid), fn(_fn), imin(_inmin), imax(_inmax), mean_value(m),
        standard_dev(1) {}

  GaussianVar(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
              const InVal &_inmin, const InVal &_inmax, DistVal sdev)
      : id(varid), fn(_fn), imin(_inmin), imax(_inmax), standard_dev(sdev) {
    mean_value = (upper() + lower()) / static_cast<OutVal>(2);
  }

  GaussianVar(const std::string &varid, const std::function<OutVal(InVal)> &_fn,
              const InVal &_inmin, const InVal &_inmax)
      : id(varid), fn(_fn), imin(_inmin), imax(_inmax), standard_dev(1) {
    mean_value = (upper() + lower()) / static_cast<OutVal>(2);
  }

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
struct ContRandomVar<InVal, OutVal, DistVal,
                     GaussianVar<InVal, OutVal, DistVal>> {
  bool mean(const GaussianVar<InVal, OutVal, DistVal> &var,
            OutVal &oval) const {
    oval = var.mean_value;
    return true;
  }

  /**
    Implementing pdf for the gaussian from
    Biagini and Campanino 2016, p. 51
    \f[\frac{1}{\sigma \sqrt(2 \pi)} e^{- \frac{(y-m)^2}{2 \sigma^2} }
  */
  bool pdf(const GaussianVar<InVal, OutVal, DistVal> &var, OutVal x,
           DistVal &out) const {
    if (var.standard_dev <= static_cast<DistVal>(0)) {
      return false;
    }
    OutVal o_mean = var.mean_value;
    OutVal o_val = x - o_mean;
    auto diff2 = o_val * o_val;

    auto sdev = static_cast<OutVal>(var.standard_dev);
    auto sigma2 = sdev * sdev * 2;
    OutVal e_diff = std::exp(-1 * diff2 / sigma2);

    OutVal K = sdev * std::sqrt(2 * static_cast<OutVal>(M_PI));
    out = static_cast<DistVal>(e_diff / K);
    return true;
  }
};

} // namespace randomvar
