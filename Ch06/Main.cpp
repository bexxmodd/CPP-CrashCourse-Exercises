#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <type_traits>
#include <stdexcept>

// 6.1
int mode(const int* values, size_t length)
{
    std::cout << "Called Int Mode\n";
    std::unordered_map<int, int> counter;
    for (int i = 0; i < length; i++)
    {
        if (counter.find(values[i]) == counter.end())
            counter.insert(std::pair<int, int>(values[i], 1));
        else
            counter[values[i]]++;
    }

    int mod = values[0];
    int max = INT_MIN;
    for (auto &entry : counter)
    {
        if (entry.second > max)
        {
            mod = entry.first;
            max = entry.second;
        }
    }
    return mod;
}

// 6.2
template<typename T>
concept Integer = std::is_arithmetic<T>::value;

template<Integer T>
T tmp_mode(T *values, size_t length)
{
    std::cout << "Called Template Mode\n";
    std::unordered_map<T, int> counter;
    for (int i = 0; i < length; i++)
    {
        if (counter.find(values[i]) == counter.end())
            counter.insert(std::pair<T, int>(values[i], 1));
        else
            counter[values[i]]++;
    }

    int mod = values[0];
    int max = INT_MIN;
    for (auto &entry : counter)
    {
        if (entry.second > max)
        {
            mod = entry.first;
            max = entry.second;
        }
    }
    return mod;
}


template<typename T, typename... Arguments>
T mean(const Arguments&... args)
requires std::is_arithmetic<T>::value
{
    constexpr size_t length{ sizeof...(args) };
    T sum = (args + ...);
    return sum / ((T)length);
}

int main()
{
    int arr[] = {10, 12, 13, 11, 12, 10, 10, 33, 5};
    int m = tmp_mode(arr, 9);
    std::cout << "Mode : " << m << std::endl;

    float flarr[] = {1.1, 4.2, 5.0, 2.3, 2.0};
    int res = mean<int>(4, 12, 3, 1);
    int res2 = mean<int>(4);
    std::cout << "Mean : " << res << std::endl;
    std::cout << "Mean : " << res2 << std::endl;
    return 0;
}