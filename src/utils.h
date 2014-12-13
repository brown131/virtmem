#ifndef UTILS_H
#define UTILS_H

#include "wrapper.h"

#include <stdio.h> // UNDONE

// Generic NULL type
class CNILL
{
public:
    template <typename T> inline operator T*(void) const { return 0; }
    template <typename T, typename A> inline operator CVirtPtr<T, A>(void) const { return CVirtPtr<T, A>(); }
    inline operator CVirtPtrBase(void) const { return CVirtPtrBase(); }
    template <typename T, typename A> inline operator typename CVirtPtr<T, A>::CValueWrapper(void) const { return CVirtPtr<T, A>::CValueWrapper(0); }

} extern const NILL;

template <typename TV> class CPtrWrapLock
{
    static int locks;
    TV ptrWrap;

public:
    CPtrWrapLock(const TV &w, bool ro=false) : ptrWrap(w) { lock(ro); }
    ~CPtrWrapLock(void) { unlock(); }

    void lock(bool ro=false) { ++locks; TV::getAlloc()->lock(ptrWrap.ptr, ro); printf("locks: %d\n", locks); }
    void unlock(void) { --locks; TV::getAlloc()->unlock(ptrWrap.ptr); printf("locks: %d\n", locks); }
    void *operator *(void) { return TV::getAlloc()->read(ptrWrap.ptr, sizeof(typename TV::TPtr)); }
};

template <typename T> int CPtrWrapLock<T>::locks;

// Shortcut
template <typename T> CPtrWrapLock<T> makePtrWrapLock(const T &w, bool ro=false) { return CPtrWrapLock<T>(w, ro); }

template <typename T, typename A> CVirtPtr<T, A> memcpy(CVirtPtr<T, A> &dest, const CVirtPtr<T, A> &src, size_t size)
{
    for (size_t s=0; s<size; ++s)
        ((CVirtPtr<uint8_t, A>)dest)[s] = ((CVirtPtr<uint8_t, A>)src)[s];
    return dest;
}

#endif // UTILS_H
