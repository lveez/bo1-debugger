/* MinHook wrappers */
#pragma once

#include <MinHook.h>
#include "../stdc++.hpp"

namespace memory {

class Hook {
   public:
    Hook();
    ~Hook() = default;

    void Enable();
    void Disable();

    template <typename T, typename Y>
    void Create(T fn_to_hook, Y detour_fn, bool enable) {
        Create_(reinterpret_cast<LPVOID>(fn_to_hook), reinterpret_cast<LPVOID>(detour_fn), enable);
    }

    template <typename T, typename... Args>
    T CallOriginal(Args... args) {
        return reinterpret_cast<T (*)(Args...)>(original_)(args...);
    }

   private:
    void Create_(LPVOID fn_to_hook, LPVOID detour_fn, bool enable);

    LPVOID address_{nullptr};
    LPVOID original_{nullptr};

    bool enabled_;
};

};  // namespace memory