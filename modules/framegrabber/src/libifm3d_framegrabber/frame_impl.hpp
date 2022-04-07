// -*- c++ -*-
/*
 * Copyright 2022-present ifm electronic, gmbh
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IFM3D_FG_FRAME_IMPL_H
#define IFM3D_FG_FRAME_IMPL_H

#include <map>
#include <ifm3d/fg/frame.h>

namespace ifm3d
{
  //============================================================
  // Impl interface
  //============================================================
  class Frame::Impl
  {
  public:
    Impl(const std::map<ImageId, Image>& images,
         const std::vector<TimePointT> timestamps);

    std::vector<ifm3d::TimePointT> TimeStamps();

    bool HasImage(ImageId id);

    Image& GetImage(ImageId id);

    decltype(std::declval<std::map<ImageId, Image>>().begin())
    begin() noexcept;
    decltype(std::declval<const std::map<ImageId, Image>>().begin()) begin()
      const noexcept;
    decltype(std::declval<std::map<ImageId, Image>>().end()) end() noexcept;
    decltype(std::declval<const std::map<ImageId, Image>>().end()) end()
      const noexcept;

  protected:
    //---------------------
    // State
    //---------------------
    std::map<ImageId, Image> images_;
    std::vector<TimePointT> timestamps_;

  }; // end: class FrameGrabber::Impl

} // end: namespace ifm3d

ifm3d::Frame::Impl::Impl(const std::map<ImageId, Image>& images,
                         const std::vector<TimePointT> timestamps)
  : images_(images),
    timestamps_(timestamps)
{}

std::vector<ifm3d::TimePointT>
ifm3d::Frame::Impl::TimeStamps()
{
  return timestamps_;
}

bool
ifm3d::Frame::Impl::HasImage(ImageId id)
{
  return images_.find(id) != images_.end();
}

ifm3d::Image&
ifm3d::Frame::Impl::GetImage(ImageId id)
{
  return images_[id];
}

decltype(std::declval<std::map<ifm3d::ImageId, ifm3d::Image>>().begin())
ifm3d::Frame::Impl::begin() noexcept
{
  return images_.begin();
}

decltype(std::declval<const std::map<ifm3d::ImageId, ifm3d::Image>>().begin())
ifm3d::Frame::Impl::begin() const noexcept
{
  return images_.begin();
}

decltype(std::declval<std::map<ifm3d::ImageId, ifm3d::Image>>().end())
ifm3d::Frame::Impl::end() noexcept
{
  return images_.end();
}

decltype(std::declval<const std::map<ifm3d::ImageId, ifm3d::Image>>().end())
ifm3d::Frame::Impl::end() const noexcept
{
  return images_.end();
}

//============================================================
// Impl -- Implementation Details
//============================================================

#endif // IFM3D_FG_FRAME_IMPL_H