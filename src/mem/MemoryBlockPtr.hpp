#pragma once


///////////////////////////////////////////////////////////

namespace rts::mem {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T>
static void FreeBlock(idx_t);

///////////////////////////////////////////////////////////

TEMPLATE struct BlockPtr
{
    idx_t blockIdx = 0;
    T* ptr = nullptr;

    BlockPtr() = default;
    BlockPtr(T*, idx_t);
    ~BlockPtr();
    void Free();

    BlockPtr(const BlockPtr&) = delete;
    auto& operator=(const BlockPtr&) = delete;

    BlockPtr(BlockPtr&&);
    auto& operator=(BlockPtr&&);

    auto* operator->() { return  ptr; }
    auto& operator* () { return *ptr; }

    auto& operator[](idx_t i) { return (*ptr)[i]; }   
};

////////////////////////////////////////////////////////////

TEMPLATE 
BlockPtr<T>::~BlockPtr()
{
    Free();
}

///////////////////////////////////////////////////////////

TEMPLATE 
void BlockPtr<T>::Free()
{
    if (ptr == nullptr) return;
    ptr->~T(); 
    FreeBlock(blockIdx);
}

///////////////////////////////////////////////////////////

TEMPLATE 
BlockPtr<T>::BlockPtr(T* pPtr, idx_t pBlockIdx)
: blockIdx { pBlockIdx }
, ptr { pPtr }
{}

///////////////////////////////////////////////////////////

TEMPLATE 
BlockPtr<T>::BlockPtr(BlockPtr&& other) 
: blockIdx { other.blockIdx } 
, ptr      { other.ptr }
{ 
    other.ptr = nullptr;
}

///////////////////////////////////////////////////////////

TEMPLATE
auto& BlockPtr<T>::operator=(BlockPtr&& other)           
{ 
    Free();
    ptr = other.ptr; 
    blockIdx = other.blockIdx;
    other.ptr = nullptr; 
    return *this; 
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns