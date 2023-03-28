#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

template <std::size_t i>
struct fixed_string {
    constexpr fixed_string(const char(&arr)[i + 1]) {
        std::copy_n(arr, i + 1, data);
    }

    constexpr auto size() const { return i; }

    template <auto I>
    constexpr auto nth_element() const {
        return data[I];
    }

    auto operator<=>(const fixed_string&) const = default;

    char data[i + 1] = {};
};

template <std::size_t i>
fixed_string(const char(&arr)[i])->fixed_string<i - 1>;

constexpr std::tuple collision_theory{
        fixed_string{"Collions Theory Is:"},
        fixed_string{"  - A collision between the reacting particles"},
        fixed_string{"  - The particles must be facing the right way up"},
        fixed_string{"  - The particles must have enough energy to react"},
        fixed_string{"      This is needed to break the bonds in the reactants"
    }
};

template<typename... Ts>
constexpr auto for_each(std::tuple<Ts...> tup, auto lamda)
{
    return[&]<std::size_t... indexes>(std::index_sequence<indexes...>)
    {
        (std::get<indexes>(tup), ...);
    }(std::make_index_sequence<sizeof...(Ts)>{});
}

int main()
{
    for_each(collision_theory, [](auto x) {std::cout << x.data(); });
}