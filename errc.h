#ifndef LIBERRC_ERRC_H
#define LIBERRC_ERRC_H

#include <type_traits>
#include <ostream>
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

    ErrorValue();
    ErrorValue(const ErrorValue &ev);
    ErrorValue(T value_, E error_);

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

    E min() const;
    E max() const;

protected:

    int numberDefaultErrorIsZero = DEF_ERROR_ZERO;
    std::function<E(T)> defaultErrorCalcFunction = nullptr;

};

template <typename T, typename E>
std::ostream& operator<<(std::ostream& os, const ErrorValue<T,E> &ev);

#endif //LIBERRC_ERRC_H
