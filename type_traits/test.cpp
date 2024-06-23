#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include "type_traits.h"
#include "test.h"

using namespace my_type_traits;

template<int N>
struct fib {
    constexpr static int value = fib<N-1>::value + fib<N-2>::value;
};

template<>
struct fib<0> {
    constexpr static int value = 1;
};

template<>
struct fib<1> {
    constexpr static int value = 1;
};

void test0() {
    static_assert(fib<2>::value == 2, "assert fib<2> == 2");
    static_assert(fib<3>::value == 3, "assert fib<3> == 3");
    static_assert(fib<4>::value == 5, "assert fib<4> == 5");
    static_assert(fib<5>::value == 8, "assert fib<5> == 8");
}

template<typename ...Args, int ...__seq>
void tuple_travel(std::tuple<Args...> a, integer_seq<__seq...> b) {
    (std::cout << ... << std::get<__seq>(a)) << std::endl;
}

void test1() {
    std::tuple<int, int, int> tp0{0, 1, 2};
    tuple_travel(tp0, make_seq_index<std::tuple_size_v<decltype(tp0)>>{});

    std::tuple<int, float, double> tp1{0, 1, 2};
    tuple_travel(tp1, make_seq_index<std::tuple_size_v<decltype(tp1)>>{});
}




void test2() {
    tuple<int, float, double> tp{1, 2, 3};
    std::cout << get<0>(tp) << std::endl;
    std::cout << get<1>(tp) << std::endl;
    std::cout << get<2>(tp) << std::endl;

    std::cout << tuple_size_v<decltype(tp)> <<std::endl;

    apply([](int a, float b, double c) {
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;
    }, tp);

    std::cout << __is_class(decltype(tp)) << std::endl;
    std::cout << __is_final(decltype(tp)) << std::endl;


}