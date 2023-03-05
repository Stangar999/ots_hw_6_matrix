#include <gtest/gtest.h>

#include <iostream>
#include <tuple>
#include <vector>

#include "matrix.h"

using namespace std::literals;

std::vector<std::vector<std::string>> ReadInput(std::istream& in);

TEST(CorrectMatrix, DefaultCheck) {
  Matrix<int, -1> matrix;
  ASSERT_EQ(matrix.size(), 0);

  auto a = matrix[0][0];
  ASSERT_EQ(static_cast<int>(a), -1);
  ASSERT_EQ(matrix.size(), 0);

  matrix[100][100] = 314;
  matrix[105][100] = 214;
  matrix[108][100] = 114;
  ASSERT_EQ(static_cast<int>(matrix[100][100]), 314);
  ASSERT_EQ(matrix.size(), 3);

  std::stringstream in;

  for (auto c : matrix) {
    auto [x, y, v] = c;
    in << x << " " << y << " " << v << std::endl;
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
