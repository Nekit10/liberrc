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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}