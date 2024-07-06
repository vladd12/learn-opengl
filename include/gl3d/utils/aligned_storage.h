#pragma once

#include <type_traits>
#include <utility>

namespace utils
{

/// \brief Data type for hiding internal data types on top level classes.
template <std::size_t Size, std::size_t Alignment> //
struct aligned_storage
{
    static_assert(Size > 0 && Alignment > 0, "Incorrect Size and Alignment for storage");
    alignas(Alignment) std::uint8_t data[Size];

    /// \brief Returns pointer to the storage data.
    inline void *get_storage_pointer()
    {
        return std::addressof(data[0]);
    }

    /// \brief Starting lifetime for new object in storage data.
    template <typename T, typename... Args>            //
    inline T *start_lifetime_as(Args... args)          //
        noexcept(noexcept(T(std::declval<Args>()...))) //
    {
        static_assert(sizeof(T) <= Size, "Datatype T too big for current storage");
        return new (get_storage_pointer()) T(std::forward<Args>(args)...);
    }

    /// \brief Returns pointer to object, that was created in storage data.
    template <typename T> //
    inline T *get_object_from_storage() noexcept
    {
        /// TODO: Some data type checks we need here :c
        return static_cast<T *>(get_storage_pointer());
    }

    /// \brief Destroying object, that was created in storage data.
    template <typename T> //
    void end_lifetime_as() noexcept
    {
        get_object_from_storage<T>()->~T();
    }
};

} // namespace utils
