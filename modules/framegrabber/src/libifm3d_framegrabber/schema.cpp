/*
 * Copyright 2018-present ifm electronic, gmbh
 * Copyright 2017 Love Park Robotics, LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ifm3d/fg/schema.h>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <ifm3d/device/util.h>
#include <ifm3d/device/err.h>
#include <ifm3d/contrib/nlohmann/json.hpp>

const std::map<ifm3d::image_id, const nlohmann::json> o3d_schema_map{
  {ifm3d::image_id::RADIAL_DISTANCE,
   {{"type", "blob"}, {"id", "distance_image"}}},
  {ifm3d::image_id::AMPLITUDE,
   {{"type", "blob"}, {"id", "normalized_amplitude_image"}}},
  {ifm3d::image_id::RAW_AMPLITUDE,
   {{"type", "blob"}, {"id", "amplitude_image"}}},
  {ifm3d::image_id::GRAY, {{"type", "blob"}, {"id", "grayscale_image"}}},
  {ifm3d::image_id::CARTESIAN_X, {{"type", "blob"}, {"id", "x_image"}}},
  {ifm3d::image_id::CARTESIAN_Y, {{"type", "blob"}, {"id", "y_image"}}},
  {ifm3d::image_id::CARTESIAN_Z, {{"type", "blob"}, {"id", "z_image"}}},
  {ifm3d::image_id::UNIT_VECTOR_ALL,
   {{"type", "blob"}, {"id", "all_unit_vector_matrices"}}},
  {ifm3d::image_id::INTRINSIC_CALIBRATION,
   {{"type", "blob"}, {"id", "intrinsic_calibration"}}},
  {ifm3d::image_id::INVERSE_INTRINSIC_CALIBRATION,
   {{"type", "blob"}, {"id", "inverse_intrinsic_calibration"}}},
  {ifm3d::image_id::JSON_MODEL, {{"type", "blob"}, {"id", "json_model"}}},
  {ifm3d::image_id::CONFIDENCE,
   {{"type", "blob"}, {"id", "confidence_image"}}},
  {ifm3d::image_id::EXTRINSIC_CALIBRATION,
   {{"type", "blob"}, {"id", "extrinsic_calibration"}}},
  {ifm3d::image_id::EXPOSURE_TIME,
   nlohmann::json::array(
     {{{"type", "string"}, {"id", "exposure_times"}, {"value", "extime"}},
      {{"type", "uint32"},
       {"id", "exposure_time_1"},
       {"format", {{"dataencoding", "binary"}, {"order", "little"}}}},
      {{"type", "uint32"},
       {"id", "exposure_time_2"},
       {"format", {{"dataencoding", "binary"}, {"order", "little"}}}},
      {{"type", "uint32"},
       {"id", "exposure_time_3"},
       {"format", {{"dataencoding", "binary"}, {"order", "little"}}}}})},
  {ifm3d::image_id::ILLUMINATION_TEMP,
   nlohmann::json::array(
     {{{"type", "string"}, {"id", "temp_illu"}, {"value", "temp_illu"}},
      {{"type", "float32"},
       {"id", "temp_illu"},
       {"format", {{"dataencoding", "binary"}, {"order", "little"}}}}})},
};

// TODO : update this for O3R specific Data.
const std::map<ifm3d::image_id, const nlohmann::json> o3r_schema_map
{
  {ifm3d::image_id::RADIAL_DISTANCE,
   {{"type", "blob"}, {"id", "RADIAL_DISTANCE_COMPRESSED"}}},
    {ifm3d::image_id::AMPLITUDE,
     {{"type", "blob"}, {"id", "AMPLITUDE_COMPRESSED"}}},
    {ifm3d::image_id::ALGO_DEBUG, {{"type", "blob"}, {"id", "ALGO_DEBUG"}}},
#if 0
  {ifm3d::image_id::REFlECTIVITY, {{"type", "blob"}, {"id", "REFLECTIVITY"}}},
#endif
    {ifm3d::image_id::INTRINSIC_CALIBRATION,
     {{"type", "blob"}, {"id", "intrinsic_calibration"}}},
    {ifm3d::image_id::INVERSE_INTRINSIC_CALIBRATION,
     {{"type", "blob"}, {"id", "inverse_intrinsic_calibration"}}},
    {ifm3d::image_id::DISTANCE_NOISE,
     {{"type", "blob"}, {"id", "RADIAL_DISTANCE_NOISE"}}},
    {ifm3d::image_id::O3R_DISTANCE_IMAGE_INFORMATION,
     {{"type", "blob"}, {"id", "TOF_INFO"}}},
    {ifm3d::image_id::JPEG, {{"type", "blob"}, {"id", "JPEG_IMAGE"}}},
    {ifm3d::image_id::CONFIDENCE, {{"type", "blob"}, {"id", "CONFIDENCE"}}},
#if 0
    {ifm3d::image_id::O3R_RGB_IMAGE_INFO,  {{"type", "blob"}, {"id", "O3R_RGB_IMAGE_INFO"}}},
#endif
};

std::string
ifm3d::make_o3x_json_from_mask(const std::set<ifm3d::image_id>& image_ids)
{
  std::map<size_t, std::string> bool_to_string{{0, "false"}, {1, "true"}};

  nlohmann::json schema = {
    {"Apps", nlohmann::json::array({{{"Index", "1"}}})}};

  auto& app_json_pointer = schema["/Apps/0"_json_pointer];

  app_json_pointer["OutputDistanceImage"] =
    bool_to_string[image_ids.count(ifm3d::image_id::RADIAL_DISTANCE)];
  app_json_pointer["OutputAmplitudeImage"] =
    bool_to_string[image_ids.count(ifm3d::image_id::AMPLITUDE)];
  app_json_pointer["OutputGrayscaleImage"] =
    bool_to_string[image_ids.count(ifm3d::image_id::GRAY)];
  app_json_pointer["OutputXYZImage"] =
    bool_to_string[image_ids.count(ifm3d::image_id::XYZ) ||
                   image_ids.count(ifm3d::image_id::CARTESIAN_ALL) ||
                   image_ids.count(ifm3d::image_id::CARTESIAN_X) ||
                   image_ids.count(ifm3d::image_id::CARTESIAN_Y) ||
                   image_ids.count(ifm3d::image_id::CARTESIAN_Z)];
  app_json_pointer["OutputDistanceNoiseImage"] =
    bool_to_string[image_ids.count(ifm3d::image_id::DISTANCE_NOISE)];
  app_json_pointer["OutputConfidenceImage"] =
    bool_to_string[image_ids.count(ifm3d::image_id::CONFIDENCE)];

  return schema.dump();
}

std::string
ifm3d::make_schema(const std::set<ifm3d::image_id>& image_ids,
                   ifm3d::Device::device_family device_type)
{
  if (device_type == ifm3d::Device::device_family::O3X)
    {
      return make_o3x_json_from_mask(image_ids);
    }

  auto check_for_device_support =
    [](const ifm3d::image_id image_id,
       const std::map<ifm3d::image_id, const nlohmann::json>& schema_map)
    -> nlohmann::json {
    if (schema_map.find(image_id) != schema_map.end())
      {
        return schema_map.at(image_id);
      }
    else
      {
        // TODO: should we throw if schema generation fail due to non supported
        // chunk_id by device ? throw
        // ifm3d::error_t(IFM3D_UNSUPPORTED_SCHEMA_ON_DEVICE);
      }
    return {};
  };

  nlohmann::json schema = {
    {"layouter", "flexible"},
    {"format", {{"dataencoding", "ascii"}}},
    {"elements",
     nlohmann::json::array(
       {{{"type", "string"}, {"value", "star"}, {"id", "start_string"}}})}};

  auto& elements = schema["/elements"_json_pointer];

  auto schema_generator =
    [&](const std::map<ifm3d::image_id, const nlohmann::json>& schema_map) {
      for (const auto chunk_id : image_ids)
        {
          auto json_schema_for_id =
            check_for_device_support(chunk_id, schema_map);

          if (json_schema_for_id.is_array())
            {
              for (const auto& val : json_schema_for_id)
                {
                  elements.push_back(val);
                }
            }
          else
            {
              elements.push_back(json_schema_for_id);
            }
        }
    };

  if (device_type == ifm3d::Device::device_family::O3D)
    {
      schema_generator(o3d_schema_map);
    }
  else if (device_type == ifm3d::Device::device_family::O3R)
    {
      schema_generator(o3r_schema_map);
      // TODO how to enable exposure time for O3R ?
    }

  // Add stop to the schema
  elements.push_back(
    {{"type", "string"}, {"value", "stop"}, {"id", "end_string"}});
  return schema.dump();
}