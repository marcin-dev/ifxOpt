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
    SharedPtr(T *ptr = nullptr) : mPtr(ptr), mRefCount(new unsigned int(0u))
    {
        if (mPtr != nullptr)
        {
            (*mRefCount)++;
        }
    }

    SharedPtr(const SharedPtr &src) noexcept : mPtr(src.mPtr), mRefCount(src.mRefCount)
    {
        if (mPtr != nullptr)
        {
            (*mRefCount)++;
        }
    }

    virtual ~SharedPtr() noexcept
    {
        if (*mRefCount > 0u && mPtr != nullptr)
        {
            (*mRefCount)--;

            if (*mRefCount == 0u)
            {
                delete mPtr; // TODO: custom deleter
                mPtr = nullptr;
                delete mRefCount;
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
            if (*mRefCount > 0u && mPtr != nullptr)
            {
                (*mRefCount)--;

                if (*mRefCount == 0u)
                {
                    delete mPtr; // TODO: custom deleter
                }
            }

            if (*mRefCount > 0u) // there are other references, need to create new control data
            {
                mRefCount = new unsigned int(0u);
            }

            mPtr = ptr;
            if (ptr != nullptr)
            {
                *mRefCount++;
            }
        }

        return *this;
    }

    SharedPtr& operator=(SharedPtr& src) noexcept
    {
        if (&src != this)  // protection from self-copying
        {
            if (*mRefCount > 0u && mPtr != nullptr)
            {
                (*mRefCount)--;

                if (*mRefCount == 0u)
                {
                    delete mPtr; // TODO: custom deleter
                    delete mRefCount;
                }
            }
            else
            {
                delete mRefCount;
            }

            mPtr      = src.mPtr;
            mRefCount = src.mRefCount;
            if (mPtr != nullptr)
            {
                (*mRefCount)++;
            }
        }

        return *this;
    }

    T& operator*() const noexcept
    {
        return *mPtr;
    }

    T* operator->() const noexcept
    {
        return mPtr;
    }
};

} /* namespace ifx */

#endif /* INCLUDE_UTILS_IFX_SHARED_PTR_H */
