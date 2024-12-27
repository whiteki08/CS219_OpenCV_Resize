#ifndef RESIZE_CUSTOM_HPP
#define RESIZE_CUSTOM_HPP

#include "precomp.hpp"

void resize_custom(const cv::Mat& input, cv::Mat& output, const cv::Size& new_size, int interpol);

#endif // RESIZE_CUSTOM_HPP