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

TEST(ErrorValueConstructors, DefaultConstructorTest) {
    ErrorValue<> a = ErrorValue();
    ASSERT_EQ(a.value, 0);
    ASSERT_EQ(a.error, 0);
}

TEST(ErrorValueConstructors, ValueAndCopyConstructorTest) {
    ErrorValue a = ErrorValue(10.0, 2.0);
    ASSERT_EQ(a.value, 10) << "Value constructor error";
    ASSERT_EQ(a.error, 2) << "Value constructor error";

    ErrorValue b(a);
    ASSERT_EQ(b.value, 10) << "Copy constructor error";
    ASSERT_EQ(b.error, 2) << "Copy constructor error";

    b.value = 5;
    b.error = 1;

    ASSERT_EQ(a.value, 10) << "Copy constructor changes original";
    ASSERT_EQ(a.error, 2) << "Copy constructor changes original";
}


TEST(ErrorValueAssigmentOperators, CopyAssigmentOpertaor) {
    ErrorValue a = ErrorValue(10.0, 2.0);
    ErrorValue<double, double> b;
    b = a;
    ASSERT_EQ(b.value, 10) << "Copy assigment operator error";
    ASSERT_EQ(b.error, 2) << "Copy assigment operator error";

    b.value = 5;
    b.error = 1;

    ASSERT_EQ(a.value, 10) << "Copy assigment operator changes original";
    ASSERT_EQ(a.error, 2) << "Copy assigment operator changes original";
}

TEST(ErrorValueAssigmentOperators, DoubleAssigmentOpertaor) {
    ErrorValue<double, double> a;

    a.setDefaultErrorCalculationMethod(ErrorValue<>::DEF_ERROR_ZERO);
    a = 5;
    ASSERT_EQ(a.value, 5) << "Setting value in assigment operator error";
    ASSERT_EQ(a.error, 0) << "Setting error (ErrorValue::DEF_ERROR_ZERO) in assigment operator error";

    a.setDefaultErrorCalculationMethod(ErrorValue<>::DEF_ERROR_HALF);
    a = 10;
    ASSERT_EQ(a.value, 10) << "Setting value in assigment operator error";
    ASSERT_EQ(a.error, 5) << "Setting error (ErrorValue::DEF_ERROR_HALF) in assigment operator error";
    a = 1;
    ASSERT_EQ(a.value, 1) << "Setting value in assigment operator error";
    ASSERT_EQ(a.error, 0.5)  << "Setting error (ErrorValue::DEF_ERROR_HALF) in assigment operator error";
    a = 0;
    ASSERT_EQ(a.value, 0) << "Setting value in assigment operator error";
    ASSERT_EQ(a.error, 0.5) << "Setting error (ErrorValue::DEF_ERROR_HALF) in assigment operator error";
    a = 0.03;
    ASSERT_EQ(a.value, 0.03) << "Setting value in assigment operator error";
    ASSERT_EQ(a.error, 0.005) << "Setting error (ErrorValue::DEF_ERROR_HALF) in assigment operator error";

    a.setDefaultErrorCalculationMethod(ErrorValue<>::DEF_ERROR_FUNC, [](double x) -> double {
        return x/2;
    });
    a = 5;
    ASSERT_EQ(a.value, 5) << "Setting value in assigment operator error";
    ASSERT_NEAR(a.error, 2.5, ABSMAX) << "Setting error (ErrorValue::DEF_ERROR_FUNC) in assigment operator error";
}

TEST(ErrorValueCompoundAssigmentOperators, AdditionOperatorTest) {
    ErrorValue a(10.0, 12.4), b(2.0, 0.12);
    a += b;

    ASSERT_NEAR(a.value, 12, ABSMAX);
    ASSERT_NEAR(a.value, 12.52, ABSMAX);

    a += 6;

    ASSERT_NEAR(a.value, 18, ABSMAX);
    ASSERT_NEAR(a.value, 12.52, ABSMAX);
}



TEST(ErrorValueCompoundAssigmentOperators, SubtructionOperatorTest) {
    ErrorValue a(10.0, 12.4), b(2.0, 0.12);
    a -= b;

    ASSERT_NEAR(a.value, 8, ABSMAX);
    ASSERT_NEAR(a.value, 12.52, ABSMAX);

    a -= 6;

    ASSERT_NEAR(a.value, 2, ABSMAX);
    ASSERT_NEAR(a.value, 12.52, ABSMAX);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}