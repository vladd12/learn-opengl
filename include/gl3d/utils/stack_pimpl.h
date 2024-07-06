#pragma once

#include <type_traits>
#include <utility>

namespace utils
{

/// \brief Fast PIMPL idiom object with stack allocated memory.
/// \details Has some smart pointer's semantics.
template <typename T, std::size_t Size, std::size_t Alignment> //
struct stack_pimpl
{
private:
    alignas(Alignment) std::uint8_t data[Size];

    /// \brief Validate current specialisation in compile time.
    template <std::size_t ActualSize, std::size_t ActualAlignment> //
    static void validate() noexcept
    {
        static_assert(ActualSize == Size, "Size and sizeof(T) mismatch");
        static_assert(ActualAlignment == Alignment, "Alignment and alignof(T) mismatch");
    }

public:
    /// \brief Perfect forwarding for T c-tor's arguments.
    /// \details Placement new operator calling on stack allocated array.
    template <typename... Args> //
    inline explicit stack_pimpl(Args &&...args) noexcept(noexcept(T(std::declval<Args>()...)))
    {
        new (ptr()) T(std::forward<Args>(args)...);
    }

    /// \brief Copy c-tor for T reference.
    inline explicit stack_pimpl(const T &value) noexcept(noexcept(T(std::declval<const T &>())))
    {
        static_assert(std::is_trivial_v<T>, "T is not trivial type");
        new (ptr()) T(value);
    }

    /// \brief Move c-tor for T rvalue.
    /// \details Placement new operator calling on stack allocated array.
    inline explicit stack_pimpl(T &&value) noexcept(noexcept(T(std::declval<T>())))
    {
        static_assert(std::is_trivial_v<T>, "T is not trivial type");
        new (ptr()) T(std::move(value));
    }

    /// \brief Copy c-tor for stack_pimple reference.
    inline explicit stack_pimpl(const stack_pimpl &rhs) noexcept(noexcept(T(std::declval<const T &>())))
        : stack_pimpl(*rhs)
    {
    }

    /// \brief Move c-tor for stack_pimpl rvalue.
    inline explicit stack_pimpl(stack_pimpl &&rhs) noexcept(noexcept(T(std::declval<T>())))
        : stack_pimpl(std::move(*rhs))
    {
    }

    /// \brief Calling T's d-tor.
    inline ~stack_pimpl() noexcept
    {
        validate<sizeof(T), alignof(T)>();
        ptr()->~T();
    }

    /// \brief Assignment operator for moving the other stored object.
    inline stack_pimpl &operator=(stack_pimpl &&rhs) noexcept
    {
        *ptr() = std::move(*rhs.ptr());
    }

    /// \brief Assignment operator for moving T rvalue in the current object.
    inline stack_pimpl &operator=(T &&rhs) noexcept
    {
        *ptr() = std::move(rhs);
    }

    /// \brief Returns pointer to the holding object.
    inline T *ptr() noexcept
    {
        return reinterpret_cast<T *>(&data);
    }

    /// \brief Returns pointer to the holding object.
    /// \details Constant overload.
    inline const T *ptr() const noexcept
    {
        return reinterpret_cast<const T *>(&data);
    }

    /// \brief Returns pointer to the holding object.
    inline T *operator->() noexcept
    {
        return ptr();
    }

    /// \brief Returns pointer to the holding object.
    /// \details Constant overload.
    inline const T *operator->() const noexcept
    {
        return ptr();
    }

    /// \brief Returns refernce to the holding object.
    inline T &operator*() noexcept
    {
        return *ptr();
    }

    /// \brief Returns refernce to the holding object.
    /// \details Constant overload.
    inline const T &operator*() const noexcept
    {
        return *ptr();
    }
};

} // namespace utils
