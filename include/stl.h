#ifndef STL_H
#define STL_H
#include <algorithm>
#include <numeric>
#include <iostream>
#include <set>
#include <string>

//due to no stl.cpp file all functions define here with inine
inline int mult_3(bool flag_for_reset = false)
{
    static int i{};
    if (flag_for_reset)
        i = 0;
    return (i++ * 3);
}

inline void initial_vector_with_3_mutiplies(std::vector<int>& v, size_t size){
    mult_3(true);
    v.resize(size);
    std::generate(v.begin(),v.end(),
    []{return mult_3();}
    );    
}

inline bool condition_above(int i, int n = 0)
{
    static int condition = 0;
    if (n)
        condition = n;
    return i > condition;
}

inline int count_unique_above(std::vector<int> v, int n)
{
    condition_above(0, n);
    std::sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());
    return std::count_if(v.begin(), v.end(), 
        [](int i) {return condition_above(i);}); // 4 should be replace by n
    
}

inline std::string v_to_s(const std::string& a, int b, char separator = 2 , bool flag_sep=false)
{
    static char sep;
    if (flag_sep)
        sep = separator;
    return a + sep + std::to_string(b);
}

inline std::string vector_to_string(std::vector<int> v, char separator){
    const std::string temp{"a"};
    v_to_s(temp, 0, separator, true);
    return std::accumulate(v.rbegin() + 1, v.rend(), std::to_string(v[v.size()-1]),
            [](const std::string& a, int b){
                return v_to_s(a, b);
            });    
}




#endif //STL_H