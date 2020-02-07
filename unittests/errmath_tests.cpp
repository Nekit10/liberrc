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

TEST(HyperbolicTrigonometricFunctionsTests, Sinh) {
    ErrorValue a = sinh(ErrorValue(1.23, 0.038));
    ASSERT_NEAR(a.value, 1.564'468'479, ABSMAX);
    ASSERT_NEAR(a.error, 0.070'556'900, ABSMAX);
}

TEST(HyperbolicTrigonometricFunctionsTests, Cosh) {
    ErrorValue a = cosh(ErrorValue(1.23, 0.038));
    ASSERT_NEAR(a.value, 1.856'761'056, ABSMAX);
    ASSERT_NEAR(a.error, 0.059'449'800, ABSMAX);
}

TEST(HyperbolicTrigonometricFunctionsTests, Tanh) {
    ErrorValue a = tanh(ErrorValue(1.23, 0.038));
    ASSERT_NEAR(a.value, 0.842'579'325, ABSMAX);
    ASSERT_NEAR(a.error, 0.011'022'300, ABSMAX);
}

TEST(HyperbolicTrigonometricFunctionsTests, ArcSinh) {
    ErrorValue a = asinh(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.755'923'299, ABSMAX);
    ASSERT_NEAR(a.error, 0.029'240'300, ABSMAX);
}

TEST(HyperbolicTrigonometricFunctionsTests, ArcCosh) {
    ErrorValue a = acosh(ErrorValue(1.2, 0.038));
    ASSERT_NEAR(a.value, 0.622'362'503, ABSMAX);
    ASSERT_NEAR(a.error, 0.057'287'200, ABSMAX);
}

TEST(HyperbolicTrigonometricFunctionsTests, ArcTanh) {
    ErrorValue a = atanh(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 1.188'136'404, ABSMAX);
    ASSERT_NEAR(a.error, 0.122'147'000, ABSMAX);
}

TEST(ErrorFunctionsTests, ErrorFunction) {
    ErrorValue a = erf(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.759'523'756, ABSMAX);
    ASSERT_NEAR(a.error, 0.021'530'500, ABSMAX);
}

TEST(ErrorFunctionsTests, ComplementaryErrorFunction) {
    ErrorValue a = erfc(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.240'476'243, ABSMAX);
    ASSERT_NEAR(a.error, 0.021'530'500, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, Exponenta) {
    ErrorValue a = exp(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 2.293'318'740, ABSMAX);
    ASSERT_NEAR(a.error, 0.087'146'112, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, LogarithmB10) {
    ErrorValue a = log10(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, -0.080'921'907, ABSMAX);
    ASSERT_NEAR(a.error, 0.019'883'361, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, Exponenta2) {
    ErrorValue a = exp2(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 1.777'685'362, ABSMAX);
    ASSERT_NEAR(a.error, 0.046'823'508, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, LogarithmB2) {
    ErrorValue a = log2(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, -0.268'816'758, ABSMAX);
    ASSERT_NEAR(a.error, 0.066'051'098, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, LogarithmBe) {
    ErrorValue a = log(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.186'329'578, ABSMAX);
    ASSERT_NEAR(a.error, 0.045'783'132, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, Exponentam1) {
    ErrorValue a = log(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 1.293'318'740, ABSMAX);
    ASSERT_NEAR(a.error, 0.087'146'112, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, Logarithm1PBe) {
    ErrorValue a = log1p(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.604'315'966, ABSMAX);
    ASSERT_NEAR(a.error, 0.020'765'027, ABSMAX);
}

TEST(LogarithmicAndExponentalFunctionsTests, LogarithmBn) {
    ErrorValue a = logn(ErrorValue(0.83, 0.038), 10);
    ASSERT_NEAR(a.value, -0.080'921'907, ABSMAX);
    ASSERT_NEAR(a.error, 0.019'883'361, ABSMAX);

    a = logn(ErrorValue(2, 0.038), 10);
    ASSERT_NEAR(a.value, 0.301'029'995, ABSMAX);
    ASSERT_NEAR(a.error, 0.008'251'595, ABSMAX);
}

TEST(PowerFunctionsTests, Pow) {
    ErrorValue a = pow(ErrorValue(0.83, 0.038), 3.23);
    ASSERT_NEAR(a.value, 0.547'800'265, ABSMAX);
    ASSERT_NEAR(a.error, 0.081'008'439, ABSMAX);
}

TEST(PowerFunctionsTests, Sqrt) {
    ErrorValue a = sqrt(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.911'043'3579, ABSMAX);
    ASSERT_NEAR(a.error, 0.020'855'209, ABSMAX);
}

TEST(PowerFunctionsTests, Cbrt) {
    ErrorValue a = cbrt(ErrorValue(0.83, 0.038));
    ASSERT_NEAR(a.value, 0.939'779'637, ABSMAX);
    ASSERT_NEAR(a.error, 0.014'342'018, ABSMAX);
}

TEST(PowerFunctionsTests, Hypot) {
    ErrorValue a = hypot(ErrorValue(0.83, 0.038), ErrorValue(1.34, 0.48));
    ASSERT_NEAR(a.value, 1.576'229'678, ABSMAX);
    ASSERT_NEAR(a.error, 0.408'552'664, ABSMAX);
}

TEST(OtherFunctionsTests, Fma) {
    ErrorValue a = fma(ErrorValue(0.83, 0.038), ErrorValue(1.34, 0.48), ErrorValue(1.45566, 1.2));
    ASSERT_NEAR(a.value, 2.567'860'000, ABSMAX);
    ASSERT_NEAR(a.error, 1.265'430'917, ABSMAX);
}

TEST(OtherFunctionsTests, Abs) {
    ErrorValue a(-0.234, 0.12345);
    ASSERT_NEAR(abs(a).value, 0.234, ABSMAX);
    ASSERT_NEAR(abs(a).error, 0.12345, ABSMAX);
    ASSERT_NEAR(abs(-a).value, 0.234, ABSMAX);
    ASSERT_NEAR(abs(-a).error, 0.12345, ABSMAX);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}