#pragma once
#include <cstddef>

// True when `defs` has exactly one entry per enum value, in enum order.
// Every definition must have an `id` member. Meant to be used in a static_assert.
template <typename Def, std::size_t N, typename Id>
constexpr bool CatalogMatchesEnum(const Def(&defs)[N], Id count) {
    if (N != static_cast<std::size_t>(count)) return false;
    for (std::size_t i = 0; i < N; ++i) {
        if (static_cast<std::size_t>(defs[i].id) != i) return false;
    }
    return true;
}