// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <coroutine>
#include <optional>
#include <cstddef>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdint>

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

struct DataPoint
{
    float timestamp;
    float data;

};

// helper class to read bytes from an array

class array_streambuf : public std::basic_streambuf<char> {
public:
  array_streambuf(char *p, size_t l) {
    setg(p, p, p + l);
  }
};

class array_istream : public std::istream {
public:
  array_istream(void *p, size_t l)
  : std::istream(&buffer), buffer(reinterpret_cast<char*>(p), l)
  {
    rdbuf(&buffer);
  }

private:
  array_streambuf buffer;
};

// read float co-routine
Generator<float> read_stream(std::istream& in)
{
    uint32_t data;
    int count{};
    char byte;
    while (in.get(byte)) {
        data = data << 8 | static_cast<unsigned char>(byte);
        if (++count == 4) {
            co_yield *reinterpret_cast<float*>(&data);
            data = 0;
            count = 0;
        }
    }
}

// read struct coroutine
Generator<DataPoint> read_data(std::istream& in)
{
    std::optional<float> first{};
    for (auto next: read_stream(in)) {
        if (first) {
            co_yield DataPoint{*first, next};
            first = std::nullopt;
        }
        else {
            first = next;
        }
    }
}

std::array<uint8_t, 32> data_log {
  0, 0, 0, 0, 65, 160, 204, 205,
  61, 204, 204, 205, 65, 167, 51, 51,
  62, 76, 204, 205, 65, 166, 102, 102,
  62, 153, 153, 154, 65, 168, 204, 205
};

int main()
{
  array_istream data_stream{std::data(data_log), std::size(data_log)};
  std::cout << "Time (ms)  Data" << '\n';
  std::cout << std::fixed << std::setprecision(2);
  for (auto [timestamp, value] : read_data(data_stream)) {
    // println("{:8.2f}{:8.2f}", timestamp, value);
    std::cout << std::setw(8) << timestamp
              << std::setw(8) << value << '\n';
  }
}
