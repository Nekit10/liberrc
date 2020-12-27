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

#ifndef LIBERRC_LIBERRC_H
#define LIBERRC_LIBERRC_H

#include <type_traits>
#include <iomanip>
#include <ostream>
#include <cmath>

#if __has_include(<compare>)
#include <compare>
#endif

#if defined(__cpp_concepts) && __has_include(<concepts>)
#include <concepts>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

template <Arithmetic T = long double , std::floating_point E = long double>
class ErrorValue {

#else
template <typename T = double , typename E = double>
class ErrorValue {

    static_assert(std::is_arithmetic<T>::value && !std::is_same<T, bool>::value,
            "Type of ErrorValue value must be arithmetic, but not bool");
    static_assert(std::is_floating_point<E>::value,
                  "Type of ErrorValue error value must be float, double or long double");

#endif

public:

    static constexpr int DEF_ERROR_ZERO = 0;
    static constexpr int DEF_ERROR_HALF = 1;
    static constexpr int DEF_ERROR_FUNC = 2;

    T value;
    E error;

    //------- CONSTRUCTORS -------

    [[nodiscard]] constexpr ErrorValue() = default;
    [[nodiscard]] constexpr ErrorValue(const ErrorValue &ev) = default;
    [[nodiscard]] constexpr ErrorValue(T value_, E error_) : value(value_), error(error_) {};

    //------- ASSIGMENT OPERATORS -------

    ErrorValue& operator=(const ErrorValue &ev) {
        if (&ev != this) {
            value = ev.value, error = ev.error;
        }
        return *this;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator=(A value_) {
        value = value_;
        error = defaultNumberError(value_);
          return *this;
    }

    //------- COMPOUND ASSIGMENT OPERATORS -------

    ErrorValue operator+=(const ErrorValue &ev) {
        value += ev.value;
        error = sqrt(error*error + ev.error*ev.error);
        return *this;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator+=(A value_) {
        *this += ErrorValue(value_, defaultNumberError(value_));
        return *this;
    }

    ErrorValue operator-=(const ErrorValue &ev) {
        value -= ev.value;
        error = sqrt(error*error + ev.error*ev.error);
        return *this;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator-=(A value_) {
        *this -= ErrorValue(value_, defaultNumberError(value_));
        return *this;
    }

    ErrorValue operator*=(const ErrorValue &ev) {
        E e1 = error/value;
        E e2 = ev.error/ev.value;
        value *= ev.value;
        error = value*sqrt(e1*e1 + e2*e2);
        return *this;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator*=(A value_) {
        *this *= ErrorValue(value_, defaultNumberError(value_));
        return *this;
    }

    ErrorValue operator/=(const ErrorValue &ev) {
        E e1 = error/value;
        E e2 = ev.error/ev.value;
        value /= ev.value;
        error = value*sqrt(e1*e1 + e2*e2);
        return *this;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator/=(A value_) {
        *this /= ErrorValue(value_, defaultNumberError(value_));
        return *this;
    }

    //------- ARITHMETIC OPERATORS -------

    ErrorValue operator+(const ErrorValue &ev) const {
        ErrorValue res = *this;
        res += ev;
        return res;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator+(A value_) const {
        ErrorValue res = *this;
        res += value_;
        return res;
    }

    ErrorValue operator-(const ErrorValue &ev) const {
        ErrorValue res = *this;
        res -= ev;
        return res;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator-(A value_) const {
        ErrorValue res = *this;
        res -= value_;
        return res;
    }

    ErrorValue operator*(const ErrorValue &ev) const {
        ErrorValue res = *this;
        res *= ev;
        return res;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator*(A value_) const {
        ErrorValue res = *this;
        res *= value_;
        return res;
    }

    ErrorValue operator/(const ErrorValue &ev) const {
        ErrorValue res = *this;
        res /= ev;
        return res;
    }

#ifdef __cpp_concepts
    template <Arithmetic A>
    ErrorValue&
#else
    template <typename A>
    typename std::enable_if<std::is_arithmetic_v<A>, ErrorValue&>::type
#endif
    operator/(A value_) const {
        ErrorValue res = *this;
        res /= value_;
        return res;
    }

    ErrorValue operator+() const {
        return ErrorValue(*this);
    }

    ErrorValue operator-() const {
        return ErrorValue(-value, error);
    }

    ErrorValue& operator++() {
        value++;
        return *this;
    }

    const ErrorValue operator++(int) {
        ErrorValue tmp(*this);
        ++(*this);
        return tmp;
    }

    ErrorValue& operator--() {
        value--;
        return *this;
    }

    const ErrorValue operator--(int) {
        ErrorValue tmp(*this);
        --(*this);
        return tmp;
    }

    //------- COMPARISON OPERATORS -------

#if defined(__cpp_impl_three_way_comparison) && defined(__cpp_lib_three_way_comparison)
    auto operator<=>(const ErrorValue<T, E> &ev) const {
        return value <=> ev.value;
    }
#else

    bool operator<(const ErrorValue &ev) {
        return value < ev.value;
    }

    bool operator<=(const ErrorValue &ev) {
        return value <= ev.value;
    }
    bool operator>=(const ErrorValue &ev) {
        return value >= ev.value;
    }

    bool operator>(const ErrorValue &ev) {
        return value > ev.value;
    }

#endif

    bool operator==(const ErrorValue &ev) {
        return value = ev.value;
    }

    bool operator!=(const ErrorValue &ev) {
        return value != ev.value;
    }


    //------- MEMBER OPERATORS -------

    long double operator[](int i) const {
        switch(i) {
            case 0:
                return value;
            case 1:
                return error;
            default:
                throw std::range_error("ErrorValue index must be 0 or 1");
        }
    }

    //------- STATIC_CAST CONVERSION OPERATORS -------

#ifdef __cpp_concepts
    template <Arithmetic A>
#else
    template<typename A, typename = typename std::enable_if<std::is_arithmetic_v<A>>::type>
#endif
    explicit operator A() const {
        return value;
    };

    //------- VOID METHODS -------

#ifdef __cpp_lib_concepts
    template <Arithmetic AT, std::floating_point AE>
    void
#else
    template <typename AT, typename AE>
    typename std::enable_if<std::is_arithmetic_v<AT> && std::is_floating_point_v<AE>, void>::type
#endif
    set(T value_, E error_) {
        value = value_;
        error = error_;
    }

    void setDefaultErrorCalculationMethod(int code, std::function<E(T)> fun = nullptr) {
        switch(code) {
            case DEF_ERROR_FUNC:
                defaultErrorCalcFunction = fun;
                [[fallthrough]];
            case DEF_ERROR_ZERO:
                [[fallthrough]];
            case DEF_ERROR_HALF:
               numberDefaultErrorCode = code;
               break;
            default:
                throw std::range_error("Invalid default error function code: " + std::to_string(code));
        }
    }

    //------- NON-VOID METHODS -------

    [[nodiscard]] E min() const {
        return value - error;
    }

    [[nodiscard]] E max() const {
        return value + error;
    }

    [[nodiscard]] int getDefaultErrorCalculationMethod() const {
        return numberDefaultErrorCode;
    }

    [[nodiscard]] std::function<E(T)> getDefaultErrorCalcFunction() const {
        if (numberDefaultErrorCode != DEF_ERROR_FUNC)
            return nullptr;
        return defaultErrorCalcFunction;
    }

protected:

    int numberDefaultErrorCode = DEF_ERROR_ZERO;
    std::function<E(T)> defaultErrorCalcFunction = nullptr;

    E defaultNumberError(T x) {
        switch (numberDefaultErrorCode) {
            case DEF_ERROR_ZERO:
                return 0;
            case DEF_ERROR_HALF:
                return halfErrorCalcFunction(x);
            [[unlikely]] case DEF_ERROR_FUNC:
                return defaultErrorCalcFunction(x);
            default:
                throw std::range_error("Invalid default error function code: " + std::to_string(numberDefaultErrorCode));
        }
    }

    E halfErrorCalcFunction(T x) {
        if (x == 0)
            return 0.5;
        if (floor(x) == x) {
            long double c = 0;
            while (static_cast<long long>(x) % 10 == 0) {
                c++;
                x /= 10;
            }
            return 5*std::pow(10, --c);
        } else {
            long double c = 0;
            while (floor(x) != x) {
                c++;
                x *= 10;
            }
            return 5*std::pow(10, -c-1);
        }
    }

};

template <typename T, typename E>
std::ostream& operator<<(std::ostream& os, const ErrorValue<T,E> &ev) {
    os << std::fixed << std::setprecision(5) <<  ev.value << " ± " << std::fixed << std::setprecision(5) << ev.error;
    return os;
}

// CMath functions

#ifndef LIBERRC_NOT_ADD_ERRMATH
    template <typename T, typename E>
    auto sin(const ErrorValue<T, E> &x) {
        return ErrorValue(std::sin(x.value), std::abs(std::cos(x.value))*x.error);
    }

    template <typename T, typename E>
    auto cos(const ErrorValue<T, E> &x) {
        return ErrorValue(std::cos(x.value), std::abs(std::sin(x.value)*x.error));
    }

    template <typename T, typename E>
    auto tan(const ErrorValue<T, E> &x) {
        return ErrorValue(std::tan(x.value), x.error/std::pow(std::cos(x.value), 2));
    }

    template <typename T, typename E>
    auto asin(const ErrorValue<T, E> &x) {
        return ErrorValue(std::asin(x.value), x.error/std::sqrt(1 - x.value*x.value));
    }

    template <typename T, typename E>
    auto acos(const ErrorValue<T, E> &x) {
        return ErrorValue(std::acos(x.value), x.error/std::sqrt(1 - x.value*x.value));
    }

    template <typename T, typename E>
    auto atan(const ErrorValue<T, E> &x) {
        return ErrorValue(std::atan(x.value), x.error/(1 + x.value*x.value));
    }

    template <typename T, typename E, typename T1, typename E1>
    auto atan2(const ErrorValue<T, E> &y, const ErrorValue<T1, E1> &x) {
        return atan(y/x);
    }

    template <typename T, typename E>
    auto sinh(const ErrorValue<T, E> &x) {
        return ErrorValue(std::sinh(x.value), std::cosh(x.value)*x.error);
    }

    template <typename T, typename E>
    auto cosh(const ErrorValue<T, E> &x) {
        return ErrorValue(std::cosh(x.value), std::abs(std::sinh(x.value))*x.error);
    }

    template <typename T, typename E>
    auto tanh(const ErrorValue<T, E> &x) {
        return ErrorValue(std::tanh(x.value), x.error/std::pow(std::cosh(x.value), 2));
    }

    template <typename T, typename E>
    auto asinh(const ErrorValue<T, E> &x) {
        return ErrorValue(std::asinh(x.value), x.error/std::sqrt(1 + x.value*x.value));
    }

    template <typename T, typename E>
    auto acosh(const ErrorValue<T, E> &x) {
        return ErrorValue(std::acosh(x.value), x.error/std::sqrt(x.value*x.value - 1));
    }

    template <typename T, typename E>
    auto atanh(const ErrorValue<T, E> &x) {
        return ErrorValue(std::atanh(x.value), x.error/(1 - x.value*x.value));
    }

    template <typename T, typename E>
    auto erf(const ErrorValue<T, E> &x) {
        return ErrorValue(
                std::erf(x.value),
                2*std::exp(-x.value*x.value)*x.error/std::sqrt(M_PI)
        );
    }

    template <typename T, typename E>
    auto erfc(const ErrorValue<T, E> &x) {
        return ErrorValue(
                std::erfc(x.value),
                2*std::exp(-x.value*x.value)*x.error/std::sqrt(M_PI)
        );
    }

    template <typename T, typename E>
    auto exp(const ErrorValue<T, E> &x) {
        return ErrorValue(std::exp(x.value), std::exp(x.value)*x.error);
    }

    template <typename T, typename E>
    auto log10(const ErrorValue<T, E> &x) {
        return ErrorValue(std::log10(x.value), x.error/(x.value * std::log(static_cast<E>(10))));
    }

    template <typename T, typename E>
    auto exp2(const ErrorValue<T, E> &x) {
        return ErrorValue(std::exp2(x.value), std::exp2(x.value)*std::log(static_cast<E>(2))*x.error);
    }

    template <typename T, typename E>
    auto log2(const ErrorValue<T, E> &x) {
        return ErrorValue(std::log2(x.value), x.error/(x.value*std::log(static_cast<E>(2))));
    }

    template <typename T, typename E>
    auto log(const ErrorValue<T, E> &x) {
        return ErrorValue(std::log(x.value), x.error/x.value);
    }

    template <typename T, typename E>
    auto expm1(const ErrorValue<T, E> &x) {
        return ErrorValue(std::expm1(x.value), std::exp(x.value)*x.error);
    }

    template <typename T, typename E>
    auto log1p(const ErrorValue<T, E> &x) {
        return ErrorValue(std::log1p(x.value), x.error/(1 + x.value));
    }

#ifdef __cpp_lib_concepts
    template <std::floating_point T, std::floating_point E, Arithmetic N>
    ErrorValue<T, E> logn(ErrorValue<T , E> x, N n) {
#else
    template <typename T, typename E, typename N>
    typename std::enable_if<std::is_floating_point<T>::value, ErrorValue<T, E>>::type
    logn(ErrorValue<T , E> x, N n) {
        static_assert(std::is_arithmetic<N>::value,
                      "Type of logn base value must be integral");
#endif
        return ErrorValue<T, E>(
                std::log(x.value)/std::log(n),
                x.error/(x.value*std::log(n))
                );
    }
#ifdef __cpp_lib_concepts
    template <std::integral T, std::floating_point E, Arithmetic N>
    ErrorValue<double, E> logn(ErrorValue<T , E> x, N n) {
#else
    template <typename T, typename E, typename N>
    typename std::enable_if<std::is_integral<T>::value, ErrorValue<double , E>>::type
    logn(ErrorValue<T , E> x, N n) {
        static_assert(std::is_integral<N>::value,
                      "Type of logn base value must be integral");
#endif
        return ErrorValue<double , E>(
                std::log(x.value)/std::log(n),
                x.error/(x.value*std::log(n))
        );
    }

    template <typename T, typename E, typename T1, typename E1>
    auto pow(const ErrorValue<T , E>& base, const ErrorValue<T1, E1>& exponent) {
        T x = base.value, y = exponent.value;
        T dx = base.error, dy = exponent.error;
        return ErrorValue(
                std::pow(x, y),
                std::sqrt(std::pow(y*std::pow(x, y - 1)*dx, 2) + std::pow(std::pow(x, y)*std::log(x)*dy, 2))
                );
    }

#ifdef __cpp_lib_concepts
template <typename T, typename E, Arithmetic N>
    auto pow(const ErrorValue<T , E>& base, N exponent) {
#else
    template <typename T, typename E, typename N>
    auto pow(const ErrorValue<T , E>& base, N exponent) {
        static_assert(std::is_arithmetic<N>::value && !std::is_same<N, bool>::value,
                      "Type of exponent base value must be arithmetic, but not bool");
#endif
        return ErrorValue(
                std::pow(base.value, exponent),
                std::abs(exponent*pow(base.value, exponent - 1))*base.error
        );
    }

    template <typename T, typename E>
    auto sqrt(const ErrorValue<T, E> &x) {
        return ErrorValue(std::sqrt(x.value), x.error/(2*std::sqrt(x.value)));
    }

    template <typename T, typename E>
    auto cbrt(const ErrorValue<T, E> &x) {
        return ErrorValue(std::cbrt(x.value), x.error/(3*std::pow(x.value, 2.0/3)));
    }

    template <typename T, typename E, typename T1, typename E1>
    auto hypot(const ErrorValue<T , E>& x_, const ErrorValue<T1, E1>& y_) {
        T x = x_.value, y = y_.value;
        T dx = x_.error, dy = y_.error;
        return ErrorValue(
                std::hypot(x, y),
                std::sqrt(pow(x*dx, 2) + std::pow(y*dy, 2))/std::sqrt(x*x + y*y)
                );
    }

    template <typename T, typename E>
    auto abs(const ErrorValue<T, E> &x) {
        return ErrorValue(std::abs(x.value), x.error);
    }

    template <typename T, typename E, typename T1, typename E1, typename T2, typename E2>
    auto fma(const ErrorValue<T, E> &x_, const ErrorValue<T1, E1> &y_, const ErrorValue<T2, E2> &z_) {
        T x = x_.value, y = y_.value, z = z_.value;
        E dx = x_.error, dy = y_.error, dz = z_.error;
        E ex = dx/x;
        E ey = dy/y;
        return ErrorValue(std::fma(x, y, z), std::sqrt(x*x*y*y*(ex*ex + ey*ey) + dz*dz));
    }

#endif //LIBERRC_ADD_ERRMATH

#endif //LIBERRC_LIBERRC_H
