// Copyright 2018 The Beam Team / Copyright 2019 The Grimm Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <vector>
#include <stdlib.h>
#include <string.h>

namespace grimm { namespace io {

template <class T, size_t DATA_SIZE> class MemPool {
public:
    explicit MemPool(size_t maxSize) :
        _maxSize(maxSize)
    {
        _pool.reserve(maxSize);
    }

    ~MemPool() {
        for (T* h: _pool) {
            free(h);
        }
    }

    T* alloc() {
        T* h = 0;
        if (!_pool.empty()) {
            h = _pool.back();
            _pool.pop_back();
        } else {
            h = (T*)calloc(1, DATA_SIZE);
        }
        return h;
    }

    void release(T* h) {
        if (_pool.size() > _maxSize) {
            free(h);
        } else {
            memset(static_cast<void*>(h), 0, DATA_SIZE);
            _pool.push_back(h);
        }
    }

private:
    using Pool = std::vector<T*>;

    Pool _pool;
    size_t _maxSize;
};

}} //namespaces

