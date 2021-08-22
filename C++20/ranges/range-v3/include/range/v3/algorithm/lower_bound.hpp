/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2014-present
//  Copyright Casey Carter 2016
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef RANGES_V3_ALGORITHM_LOWER_BOUND_HPP
#define RANGES_V3_ALGORITHM_LOWER_BOUND_HPP

#include <range/v3/range_fwd.hpp>

#include <range/v3/algorithm/aux_/lower_bound_n.hpp>
#include <range/v3/algorithm/partition_point.hpp>
#include <range/v3/functional/comparisons.hpp>
#include <range/v3/functional/identity.hpp>
#include <range/v3/iterator/operations.hpp>
#include <range/v3/iterator/traits.hpp>
#include <range/v3/range/access.hpp>
#include <range/v3/range/concepts.hpp>
#include <range/v3/range/dangling.hpp>
#include <range/v3/range/traits.hpp>
#include <range/v3/utility/static_const.hpp>

#include <range/v3/detail/disable_warnings.hpp>

namespace ranges
{
    /// \addtogroup group-algorithms
    /// @{
    RANGES_FUNC_BEGIN(lower_bound)

        /// \brief function template \c lower_bound
        template<typename I,
                 typename S,
                 typename V,
                 typename C = less,
                 typename P = identity>
        auto RANGES_FUNC(lower_bound)(
            I first, S last, V const & val, C pred = C{}, P proj = P{})
            ->CPP_ret(I)( //
                requires forward_iterator<I> && sentinel_for<S, I> &&
                indirect_strict_weak_order<C, V const *, projected<I, P>>)
        {
            return partition_point(std::move(first),
                                   std::move(last),
                                   detail::make_lower_bound_predicate(pred, val),
                                   std::move(proj));
        }

        /// \overload
        template<typename Rng, typename V, typename C = less, typename P = identity>
        auto RANGES_FUNC(lower_bound)(
            Rng && rng, V const & val, C pred = C{}, P proj = P{})
            ->CPP_ret(safe_iterator_t<Rng>)( //
                requires forward_range<Rng> &&
                indirect_strict_weak_order<C, V const *, projected<iterator_t<Rng>, P>>)
        {
            return partition_point(
                rng, detail::make_lower_bound_predicate(pred, val), std::move(proj));
        }

    RANGES_FUNC_END(lower_bound)

    namespace cpp20
    {
        using ranges::lower_bound;
    }
    /// @}
} // namespace ranges

#include <range/v3/detail/reenable_warnings.hpp>

#endif
