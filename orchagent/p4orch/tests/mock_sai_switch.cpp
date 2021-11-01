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
#include "mock_sai_switch.h"

MockSaiSwitch *mock_sai_switch;

sai_status_t mock_get_switch_attribute(_In_ sai_object_id_t switch_id, _In_ uint32_t attr_count,
                                       _Inout_ sai_attribute_t *attr_list)
{
    return mock_sai_switch->get_switch_attribute(switch_id, attr_count, attr_list);
}

sai_status_t mock_set_switch_attribute(_In_ sai_object_id_t switch_id, _In_ const sai_attribute_t *attr)
{
    return mock_sai_switch->set_switch_attribute(switch_id, attr);
}
