/*
 * Copyright 2020 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mock_sai_serialize.h"

MockSaiSerialize* mock_sai_serialize;

inline std::string sai_serialize_object_id(sai_object_id_t oid) {
  return mock_sai_serialize->sai_serialize_object_id(oid);
}

inline std::string sai_serialize_object_type(sai_object_type_t object_type) {
  return mock_sai_serialize->sai_serialize_object_type(object_type);
}
