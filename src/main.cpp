#include <cassert>
#include <iostream>
#include <ranges>
#include <unordered_map>

#include "matrix.h"
#include "version.h"

using namespace std;

int main() {
  Matrix<int, 0> matrix;
  for (int i : ranges::views::iota(0, 10)) {
    matrix[i][i] = i;
    matrix[i][9 - i] = 9 - i;
  }

  for (int r : ranges::views::iota(1, 9)) {
    for (int c : ranges::views::iota(1, 9)) {
      std::cout << matrix[c][r] << " ";
    }
    std::cout << endl;
  }

  std::cout << matrix.size() << std::endl;

  for (auto c : matrix) {
    auto [x, y, v] = c;
    std::cout << x << " " << y << " " << v << std::endl;
  }

  //    Matrix<int, -1> matrix;
  //    assert(matrix.size() == 0);

  //    auto a = matrix[0][0];
  //    assert(a == -1);
  //    assert(matrix.size() == 0);

  //    matrix[100][100] = 314;
  //    matrix[105][100] = 214;
  //    matrix[108][100] = 114;
  //    assert(matrix[100][100] == 314);
  //    //assert(matrix.size() == 1);

  //    for(auto c : matrix)
  //    {
  //        int x;
  //        int y;
  //        int v;
  //        std::tie(x, y, v) = c;
  //        std::cout << x << " " << y << " " << v << std::endl;
  //    }

  cout << "Hello World! " << version() << endl;
  return 0;
}
