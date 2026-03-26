#pragma once

#include <string>
#include <variant>

template <typename T, typename E>
struct Expected
{
    std::variant<T, E> storage;

    static Expected makeSuccess(T v) { return Expected { std::move(v) }; }
    static Expected makeFailure(E e) { return Expected { std::move(e) }; }

    bool hasValue() const { return std::holds_alternative<T>(storage); }
    const T& value() const { return std::get<T>(storage); }
    const E& error() const { return std::get<E>(storage); }
};

template <typename E>
struct Expected<void, E>
{
    bool ok;
    E e;
    
    static Expected makeSuccess() { return Expected { true, E{} }; }
    static Expected makeFailure(E error) { return Expected { false, std::move(error) }; }

    bool hasValue() const { return ok; }
    const E& error() const { return e; }
private:
    Expected(bool isOk, E error) : ok(isOk), e(std::move(error)) {}
};

template <>
struct Expected<void, std::string>
{
    std::string msg;

    static Expected makeSuccess(void) { return Expected { "" }; }
    static Expected makeFailure(std::string error) { return Expected { std::move(error) }; }

    bool hasValue() const { return msg.empty(); }
    std::string error() const { return msg; }
};