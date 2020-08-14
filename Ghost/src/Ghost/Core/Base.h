#pragma once

#include <memory>

#include "Ghost/Core/PlatformDetection.h"

#ifdef GT_DEBUG
#if defined(GT_PLATFORM_WINDOWS)
#define GT_DEBUGBREAK() __debugbreak()
#elif defined(GT_PLATFORM_LINUX)
#include <signal.h>
#define GT_DEBUGBREAK() raise(SIGTRAP)
#endif
#define GT_ENABLE_ASSERTS
#else
#define GT_DEBUGBREAK()
#endif // GT_DEBUG

#ifdef GT_ENABLE_ASSERTS
#define GT_ASSERT(x, ...) { if(!(x)) { GT_ERROR("Assetion Failed: {0}",__VA_ARGS__); GT_DEBUGBREAK(); } }
#define GT_CORE_ASSERT(x, ...) { if(!(x)) { GT_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); GT_DEBUGBREAK(); } }
#else
#define GT_ASSERT(x, ...)
#define GT_CORE_ASSERT(x, ...)
#endif // GT_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define GT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...);}

namespace Ghost {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}