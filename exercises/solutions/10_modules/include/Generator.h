// Generator.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef GENERATOR_H
#define GENERATOR_H

#include <coroutine>
#include <optional>
#include <cstddef>
#include <iterator>

template <typename T>
class Generator
{
    class Promise
    {
    public:
        using value_type = T;

        Promise() = default;
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {
            std::rethrow_exception(std::current_exception());
        }

        std::suspend_always yield_value(T value) {
            this->value = std::move(value);
            return {};
        }

        // void return_value(T value) {
        //     this->value = std::move(value);
        //     generating = false;
        // }

        void return_void() {
            generating = false;
        }

        inline Generator get_return_object();

        value_type get_value() {
            return std::move(value);
        }

        bool finished() {
            return !generating;
        }

    private:
        bool generating {true};
        value_type value{};
    };

public:
    using value_type = T;
    using promise_type = Promise;

    explicit Generator(std::coroutine_handle<Promise> handle)
        : handle (handle)
    {}

    ~Generator() {
        if (handle) { handle.destroy(); }
    }

    Promise::value_type next() {
        if (handle) {
            handle.resume();
            return handle.promise().get_value();
        }
        else {
            return {};
        }
    }

    struct end_iterator {};

    class iterator
    {
    public:
        using value_type = Promise::value_type;
        using difference_type =  std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        iterator(Generator& generator) : generator{&generator}
        {}

        value_type operator*() const {
            if (generator) {
                return generator->handle.promise().get_value();
            }
            return {};
        }

        value_type operator->() const {
            if (generator) {
                return generator->handle.promise().get_value();
            }
            return {};
        }

        iterator& operator++() {
            if (generator && generator->handle) {
                generator->handle.resume();
            }
            return *this;
        }

        iterator& operator++(int) {
            if (generator && generator->handle) {
                generator->handle.resume();
            }
            return *this;
        }

        bool operator== (const end_iterator&) const {
            return generator ? generator->handle.promise().finished() : true;
        }

    private:
        Generator* generator{};
    };

    iterator begin() {
        iterator it{*this};
        return ++it;
    }

    end_iterator end() {
        return end_sentinel;
    }

private:
    end_iterator end_sentinel{};
    std::coroutine_handle<Promise> handle;
};


template <typename T>
inline Generator<T> Generator<T>::Promise::get_return_object()
{
    return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
}

#endif
