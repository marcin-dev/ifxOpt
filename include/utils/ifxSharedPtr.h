/**
 * ifxSharedPtr.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INCLUDE_UTILS_IFX_SHARED_PTR_H
#define INCLUDE_UTILS_IFX_SHARED_PTR_H

#include <utility>

namespace ifx
{

template <typename T>
class SharedPtr
{
private:
    T *mPtr;
    unsigned int *mRefCount;

public:
    SharedPtr(T *ptr = nullptr) : mPtr(ptr),
                                  mRefCount((ptr == nullptr) ? nullptr : new unsigned int(1u))
    { }

    SharedPtr(const SharedPtr &src) noexcept : mPtr(src.mPtr), mRefCount(src.mRefCount)
    {
        if (mPtr != nullptr)
        {
            (*mRefCount)++;
        }
    }

    SharedPtr(SharedPtr &&src) noexcept : mPtr(src.mPtr), mRefCount(src.mRefCount)
    {
        if (mPtr != nullptr)
        {
            src.mPtr      = nullptr;
            src.mRefCount = nullptr;
        }
    }

    virtual ~SharedPtr() noexcept
    {
        if (mPtr != nullptr)
        {
            (*mRefCount)--;

            if (*mRefCount == 0u)
            {
                // no other references, may delete
                delete mPtr; // TODO: custom deleter
                delete mRefCount;
                mPtr      = nullptr;
                mRefCount = nullptr;

            }
        }
    }

    T *get() const noexcept
    {
        return mPtr;
    }

    void swap(SharedPtr &src) noexcept
    {
        std::swap(this->mPtr,      src.mPtr);
        std::swap(this->mRefCount, src.mRefCount);
    }

    unsigned int refCount() const noexcept
    {
        return *mRefCount;
    }

    SharedPtr& operator=(T *ptr) noexcept
    {
        if (ptr != mPtr)  // protection from self-copying
        {
            if (mPtr != nullptr)
            {
                (*mRefCount)--;

                if (*mRefCount == 0u)
                {
                    // no other references, may delete
                    delete mPtr; // TODO: custom deleter
                    delete mRefCount;
                }
            }

            if (ptr != nullptr)
            {
                mRefCount = new unsigned int(1u);
            }
            else
            {
                mRefCount = nullptr;
            }

            mPtr = ptr;
        }

        return *this;
    }

    SharedPtr& operator=(SharedPtr& src) noexcept
    {
        if (   &src != this                 // protection from self-copying
            && mRefCount != src.mRefCount)  // protection from another reference to the same pointer
        {
            if (mPtr != nullptr)
            {
                (*mRefCount)--;

                if (*mRefCount == 0u)
                {
                    delete mPtr; // TODO: custom deleter
                    delete mRefCount;
                }
            }

            mPtr      = src.mPtr;
            mRefCount = src.mRefCount;
            if (mRefCount != nullptr)
            {
                (*mRefCount)++;
            }
        }

        return *this;
    }

    T& operator*() const noexcept
    {
        return *mPtr; // no except, segmentation fault when mPtr == nullptr
    }

    T* operator->() const noexcept
    {
        return mPtr; // no except, segmentation fault when mPtr == nullptr
    }
};

} /* namespace ifx */

#endif /* INCLUDE_UTILS_IFX_SHARED_PTR_H */
