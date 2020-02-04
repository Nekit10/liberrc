#ifndef LIBERRC_ERRC_H
#define LIBERRC_ERRC_H

#include <type_traits>
#include <ostream>
#include <cmath>
#include <compare>

template <typename T = long double , typename E = long double>
class ErrorValue {

    static_assert(std::is_arithmetic<T>::value && !std::is_same<T, bool>::value,
            "Type of ErrorValue value must be arithmetic, but not bool");
    static_assert(std::is_floating_point<E>::value,
                  "Type of ErrorValue error value must be float, double or long double");

public:

    const int DEF_ERROR_ZERO = 0;
    const int DEF_ERROR_HALF = 1;
    const int DEF_ERROR_FUNC = 2;

    T value;
    E error;

    [[nodiscard]] ErrorValue();
    [[nodiscard]] ErrorValue(const ErrorValue &ev);
    [[nodiscard]] ErrorValue(T value_, E error_);

    ErrorValue& operator=(const ErrorValue &ev);
    ErrorValue& operator=(T value);

    ErrorValue operator+=(const ErrorValue &ev);
    ErrorValue operator+=(T value);
    ErrorValue operator-=(const ErrorValue &ev);
    ErrorValue operator-=(T value);
    ErrorValue operator*=(const ErrorValue &ev);
    ErrorValue operator*=(T value);
    ErrorValue operator/=(const ErrorValue &ev);
    ErrorValue operator/=(T value);

    ErrorValue operator+(const ErrorValue &ev) const;
    ErrorValue operator+(const T &value) const;
    ErrorValue operator-(const ErrorValue &ev) const;
    ErrorValue operator-(const T &value) const;
    ErrorValue operator*(const ErrorValue &ev) const;
    ErrorValue operator*(const T &value) const;
    ErrorValue operator/(const ErrorValue &ev) const;
    ErrorValue operator/(const T &value) const;
    ErrorValue operator+() const;
    ErrorValue operator-() const;
    ErrorValue& operator++();
    ErrorValue& operator++(int);
    ErrorValue& operator--();
    ErrorValue& operator--(int);

    std::weak_ordering operator<=>(const ErrorValue  &ev) const;

    E operator[](int) const;
    operator T() const;

    friend std::ostream& operator<<(std::ostream&, const ErrorValue<T,E> &);

    void set(T value, E error);
    void setDefaultErrorCalculationMethod(int code, std::function<E(T)> fun = nullptr);

    [[nodiscard]] E min() const;
    [[nodiscard]] E max() const;
    [[nodiscard]] int getDefaultErrorCalculationMethod() const;
    [[nodiscard]] std::function<E(T)> getDefaultErrorCalcFunction() const;

protected:

    int numberDefaultErrorIsZero = DEF_ERROR_ZERO;
    std::function<E(T)> defaultErrorCalcFunction = nullptr;

};

template <typename T, typename E>
std::ostream& operator<<(std::ostream& os, const ErrorValue<T,E> &ev);

// CMath functions

namespace errmath {

    template <typename T, typename E>
    auto sin(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto cos(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto tan(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto asin(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto acos(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto atan(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto atan2(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto sinh(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto cosh(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto tanh(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto asinh(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto acosh(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto atanh(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto exp(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto log(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto log10(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto exp2(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto expm1(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto log1p(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    auto log2(const ErrorValue<T, E> &x);

    template <typename T, typename E>
    typename std::enable_if<std::is_floating_point<T>::value, ErrorValue<T, E>>::type
    logn(ErrorValue<T , E> x);

    template <typename T, typename E>
    typename std::enable_if<std::is_integral<T>::value, ErrorValue<double , E>>::type
    logn(ErrorValue<T , E> x);
}

#endif //LIBERRC_ERRC_H
