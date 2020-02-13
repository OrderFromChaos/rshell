#include "gtest/gtest.h"
#include "splitOnCharTest.h"
#include "filterCommentsTest.h"
#include "groupQuotesTest.h"
#include "tokenizeTest.h"
#include "constructExpressionTreeTest.h"
#include "../integration_tests/parserTest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
