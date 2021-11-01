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
#include "mock_sai_udf.h"

MockSaiUdf *mock_sai_udf;

sai_status_t create_udf(sai_object_id_t *udf_id, sai_object_id_t switch_id, uint32_t attr_count,
                        const sai_attribute_t *attr_list)
{
    return mock_sai_udf->create_udf(udf_id, switch_id, attr_count, attr_list);
}

sai_status_t remove_udf(sai_object_id_t udf_id)
{
    return mock_sai_udf->remove_udf(udf_id);
}

sai_status_t create_udf_group(sai_object_id_t *udf_group_id, sai_object_id_t switch_id, uint32_t attr_count,
                              const sai_attribute_t *attr_list)
{
    return mock_sai_udf->create_udf_group(udf_group_id, switch_id, attr_count, attr_list);
}

sai_status_t remove_udf_group(sai_object_id_t udf_group_id)
{
    return mock_sai_udf->remove_udf_group(udf_group_id);
}

sai_status_t create_udf_match(sai_object_id_t *udf_match_id, sai_object_id_t switch_id, uint32_t attr_count,
                              const sai_attribute_t *attr_list)
{
    return mock_sai_udf->create_udf_match(udf_match_id, switch_id, attr_count, attr_list);
}

sai_status_t remove_udf_match(sai_object_id_t udf_match_id)
{
    return mock_sai_udf->remove_udf_match(udf_match_id);
}
