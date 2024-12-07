#pragma once

#define FORBID_COPY(T) \
    T(const T&) = delete; \
    T& operator=(const T&) = delete;

#define FORBID_MOVE(T) \
    T(T&&) = delete; \
    T& operator=(T&&) = delete;

#define FORBID_COPY_MOVE(T) \
    FORBID_COPY (T) \
    FORBID_MOVE (T)
