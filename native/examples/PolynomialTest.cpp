// g++ -march=native -mfpmath=sse -O3 PolynomialTest.cpp -lntl -lgmp -std=c++11 -pthread

#include "polynomial.hpp"
#include <vector>
#include <iostream>
//#include "Timer.h"

using namespace std;

int main() {
  //srand(time(NULL));
  uint64_t modulus = (1 << 13) - 1;
  int degree = 1022; // = N-2 and is even
  int n = degree + 1;
  int N = degree + 2;
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, N);
  
  long missing_index = dist(rd);
  
  cout << "Missing index " << missing_index << endl;
  
  PolynomialWithFastVerification p(modulus, N);
  //Timer t;
  vector<uint64_t> Px = p.generate_random_evaluation();
  //t.Tick("Generate challanges");  
  
  vector<uint64_t> points, values;
  for (int idx = 0; idx <= n; idx++) {
    if (idx == missing_index) continue;
    points.push_back(idx + 1);
    values.push_back(Px[idx]);
  }
  
  uint64_t answer = p.compute_p0(points, values);
  
  cout << "Answer: " << answer << endl;
  //t.Tick("Generate answer");
  
  return 0;
}