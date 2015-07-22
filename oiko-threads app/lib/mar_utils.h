
// Various C++ Utilities
// by Marinos Koutsomichalis (marinos@agxivatein.com)

/* this header is only meant for privite use - if you ever happen to use it bare in mind that no guarantee of functionlity is given */

#ifndef MAR_UTILS_H
#define MAR_UTILS_H

#include <iosfwd>
#include <random>
#include <exception>
#include <vector>
#include <algorithm>
#include <boost/type_index.hpp>

// macros
#define DEBUG_PRINT(A) std::cout << #A << ": " << (A) << std::endl; 
#define PROJECT_INFO_PRINT(A) std::cout << (A) << "\nDeveloped by (c) Marinos Koutsomichalis (marinos@agxivatein.com)\nUse at your own risk!" << std::endl;
#define PRINT_TYPE_INFO(A) std::cout <<  #A << ": "<< boost::typeindex::type_id_with_cvr< decltype((A)) >().pretty_name() << std::endl;
#define GET_VAR_NAME(a) #a

namespace mar {
  
  // ============================= randomness ========================
  template<typename T = int> // T -> numerical 
  T random(T min, T max) {
    static long long
      seed {std::chrono::system_clock::now().time_since_epoch().count()};
    static std::default_random_engine
      engine {static_cast<unsigned int>(seed)};
    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(engine);
  }
  template<typename T = int> // T -> numberical
  T random(T max) {
    static long long
      seed {std::chrono::system_clock::now().time_since_epoch().count()};
    static std::default_random_engine
      engine {static_cast<unsigned int>(seed)};
    std::uniform_int_distribution<T> distribution(0, max);
    return distribution(engine);
  }
  template<typename T = int> // T -> numerical
  std::vector<T> irregular_distribution (T sum, int parts, double deviation = 0.30) {
    if (parts < 1) throw(std::domain_error("irregular_distribute: parts should be >=1"));
    if((deviation > 1.0) || (deviation < 0)) throw(std::domain_error("irregular_distribute: deviation should be in the 0-1 range"));
    std::vector<T> result{};
    T s{sum};
    for (T i = parts; i>1; i--) {
	T a {s/i};
	T res {mar::random<T>(static_cast<T>(a * (1-deviation)),
			      static_cast<T>(a * (1+deviation)))};
	result.push_back(res);
	s -= res;
    }
    result.push_back(s); // push back last value
    std::random_shuffle(result.begin(), result.end());
    return result;
  }
}

#endif
