/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "tc/core/polyhedral/mapping_types.h"

#include "tc/external/isl.h"

namespace tc {
namespace polyhedral {
namespace mapping {
ThreadId ThreadId::makeId(size_t dim) {
  CHECK(dim < 3);
  if (dim == 0) {
    return ThreadId::x();
  }
  if (dim == 1) {
    return ThreadId::y();
  }
  return ThreadId::z();
}
ThreadId ThreadId::x() {
  static thread_local isl::id x(
      isl::with_exceptions::globalIslCtx(), std::string("t0"));
  return makeId<0>(x);
}
ThreadId ThreadId::y() {
  static thread_local isl::id y(
      isl::with_exceptions::globalIslCtx(), std::string("t1"));
  return makeId<1>(y);
}
ThreadId ThreadId::z() {
  static thread_local isl::id z(
      isl::with_exceptions::globalIslCtx(), std::string("t2"));
  return makeId<2>(z);
}

BlockId BlockId::makeId(size_t dim) {
  CHECK(dim < 3);
  if (dim == 0) {
    return BlockId::x();
  }
  if (dim == 1) {
    return BlockId::y();
  }
  return BlockId::z();
}
BlockId BlockId::x() {
  static thread_local isl::id x(
      isl::with_exceptions::globalIslCtx(), std::string("b0"));
  return makeId<0>(x);
}
BlockId BlockId::y() {
  static thread_local isl::id y(
      isl::with_exceptions::globalIslCtx(), std::string("b1"));
  return makeId<1>(y);
}
BlockId BlockId::z() {
  static thread_local isl::id z(
      isl::with_exceptions::globalIslCtx(), std::string("b2"));
  return makeId<2>(z);
}

bool MappingId::isBlockId() {
  return *this == BlockId::x() or *this == BlockId::y() or
      *this == BlockId::z();
}
BlockId* MappingId::asBlockId() {
  if (!isBlockId()) {
    return nullptr;
  }
  return static_cast<BlockId*>(this);
}
bool MappingId::isThreadId() {
  return *this == ThreadId::x() or *this == ThreadId::y() or
      *this == ThreadId::z();
}
ThreadId* MappingId::asThreadId() {
  if (!isThreadId()) {
    return nullptr;
  }
  return static_cast<ThreadId*>(this);
}
} // namespace mapping
} // namespace polyhedral
} // namespace tc
