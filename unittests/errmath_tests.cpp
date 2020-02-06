/**
 * This file is part of liberrc.
 *
 *  liberrc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of
 *  the License, or (at your option) any later version.
 *
 *  liberrc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  and GNU Lesser General Public License along with liberrc.  If not,
 *  see <https://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"

#include "errc.h"

const double ABSMAX = 0.000001;

TEST(TrigonometricFunctionsTests, Sin) {
    ErrorValue a = sin(ErrorValue(1.23, 0.038));
    ASSERT_NEAR(a.value, 0.942'488'801, ABSMAX);
    ASSERT_NEAR(a.error, 0.0127'010'336, ABSMAX);
}

TEST(TrigonometricFunctionsTests, Cos) {
    ErrorValue a = cos(ErrorValue(1.23, 0.038));
    ASSERT_NEAR(a.value, 0.334'237'727, ABSMAX);
    ASSERT_NEAR(a.error, 0.035'814'574, ABSMAX);
}

TEST(TrigonometricFunctionsTests, Tan) {
    ErrorValue a = tan(ErrorValue(1.23, 0.038));
    ASSERT_NEAR(a.value, 2.819'815'734, ABSMAX);
    ASSERT_NEAR(a.error, 0.340'151'709, ABSMAX);
}

TEST(TrigonometricFunctionsTests, ArcSin) {
    ErrorValue a = asin(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.979'107'684, ABSMAX);
    ASSERT_NEAR(a.error, 0.068'129'247, ABSMAX);
}

TEST(TrigonometricFunctionsTests, ArcCos) {
    ErrorValue a = acos(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.591'688'642, ABSMAX);
    ASSERT_NEAR(a.error, 0.068'129'247, ABSMAX);
}

TEST(TrigonometricFunctionsTests, ArcTan) {
    ErrorValue a = atan(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.692'767'835, ABSMAX);
    ASSERT_NEAR(a.error, 0.0224'998'519, ABSMAX);
}

TEST(TrigonometricFunctionsTests, ArcTan2) {
    ErrorValue a = atan2(ErrorValue(0.83, 0.038), ErrorValue(0.43, 0.134));
    ASSERT_NEAR(a.value, 1.092'795'636, ABSMAX);
    ASSERT_NEAR(a.error, 0.128'649'457, ABSMAX);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}