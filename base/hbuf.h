#pragma once

#include "hdef.h"
#include "hbase.h"

typedef struct hbuf_s
{
    char* base;
    size_t len;
    hbuf_s()
    {
        base = NULL;
        len = 0;
    }
    hbuf_s(void* data, size_t len)
    {
        this->base = (char*) data;
        this->len = len;
    }
    virtual ~hbuf_s()
    {

    }
}hbuf_t;

typedef struct offset_buf_s
{
    char* base;
    size_t len;
    size_t offset;
    offset_buf_s()
    {
        base = NULL;
        len = offset = 0;
    }
    offset_buf_s(void* data, size_t len) 
    {
        this->base = (char*) data;
        this->len = len;
        offset = 0;
    }
}offset_buf_t;

class HBuf : public hbuf_t
{
public:
    HBuf()
    {
        cleanup_ = false;
    }
    HBuf(void* data, size_t len) : hbuf_t(data, len)
    {
        cleanup_ = false;
    }
    HBuf(size_t cap) {resize(cap);}
    virtual ~HBuf()
    {
        cleanup();
    }
    void* data() {return base;}
    size_t size() {return len;}
    bool isNull() {return base == NULL || len == 0;}
    void cleanup()
    {
        if(cleanup_)
        {
            HV_FREE(base);
            len = 0;
            cleanup_ = false;
        }
    }
    void resize(size_t cap)
    {
        if(cap == len)
        {
            return;
        }
        if(base == NULL)
        {
            HV_ALLOC(base, cap);
        }
        else
        {
            base = (char*) safe_realloc(base, cap, len);
        }
        len = cap;
        cleanup_ = true;
    }
    void copy(void* data, size_t len)
    {
        resize(len);
        memcpy(base, data, len);
    }
    void copy(hbuf_t* buf)
    {
        copy(buf->base, buf->len);
    }
private:
    bool cleanup_;
};

class HVLBuf : public HBuf
{
public:
    HVLBuf() : HBuf() {_offset = _size = 0;}
    HVLBuf(void* data, size_t len) : HBuf(data, len) {_offset = 0; _size = len;}
    HVLBuf(size_t cap) : HBuf(cap) {_offset = _size = 0;}
    virtual ~HVLBuf(){}

    char* data() {return base + _offset;}
    size_t size() {return _size;}
    void push_front(void* ptr, size_t len)
    {
        if(len > this->len - _size)
        {
            size_t newsize = MAX(this->len, len)*2;
            this->len = newsize;
        }
        if(_offset < len)
        {
            memmove(base+this->len-_size, data(), _size);
            _offset = this->len - _size;
        }
        memcpy(data() - len, ptr, len);
        _offset -= len;
        _size += len;
    }
private:
    size_t _offset;
    size_t _size;
};