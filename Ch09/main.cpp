#include <cstdio>
#include <iostream>
#include <assert.h>
#include <bits/stdc++.h>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"


template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In *input, size_t length, Out initial)
{
    for (size_t i = 0; i < length; i++)
        initial = function(input[i], initial);
    return initial;
}

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length)
{
    for (size_t i = 0; i < length; i++)
        if (!function(input[i]))
            return false;
    return true;
}


TEST_CASE("fold with lambdas", "[fold]")
{
    int data[]{ 100, 200, 300, 400, 500 };
    size_t data_len = 5;

    SECTION("fold for summing numbers")
    {
        auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len, 0);
        REQUIRE(sum == 1500);
    }

    SECTION("fold for finding min value in an array")
    {
        auto min = fold([](auto x, auto y) { return x < y ? x : y; }, data, data_len, INT_MAX);
        REQUIRE(min == 100);
    }

    SECTION("fold for finding max value in an array")
    {
        auto max = fold([](auto x, auto y) { return x > y ? x : y; }, data, data_len, INT_MIN);
        REQUIRE(max == 500);
    }

    SECTION("fold to find values more than 200 in an array")
    {
        auto twohundred = fold([](auto x, auto y) { return x > 200 ? y + 1 : 0; }, data, data_len, 0);
        REQUIRE(twohundred == 3);
    }
}

TEST_CASE("find all values satisfied the requirement", "[all]")
{
    int data[]{ 99, 199, 299, 399, 499 };
    size_t data_len = 5;
    auto all_gt100 = all([](auto x) { return x > 200; }, data, data_len);
    REQUIRE(all_gt100 == false);
}

