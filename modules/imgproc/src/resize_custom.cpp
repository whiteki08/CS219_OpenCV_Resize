#include "resize_custom.hpp"

void resize_custom(const cv::Mat &input, cv::Mat &output, const cv::Size &new_size, int interpol) {}

// Bilinear Interpolation(BI)双线性插值
void resize_BI(const cv::Mat &input, cv::Mat &output, const cv::Size &new_size) {
    double scale_width = static_cast<double>(input.cols) / new_size.width;
    double scale_height = static_cast<double>(input.rows) / new_size.height;
    //  注意矩阵索引中x,y的顺序
    for (int i = 0; i < new_size.width; ++i) {
        for (int j = 0; j < new_size.height; ++j) {
            double x_src = (i + 0.5) * scale_width - 0.5;
            double y_src = (j + 0.5) * scale_height - 0.5;
            int x_1 = static_cast<int>(x_src);
            int y_1 = static_cast<int>(y_src);
            // 避免越界
            int x_2 = std::min(x_1 + 1, input.cols - 1);
            int y_2 = std::min(y_1 + 1, input.rows - 1);
            //  判断图像类型
            // 单通道图像，像素值为灰度值
            // 三通道图像，像素值为Vec3b类型
            int type = input.type();
            if (type == CV_8UC1) {
                // 从输入图像中获取上述四个坐标对应的像素值
                double p1 = input.at<uchar>(y_1, x_1);
                double p2 = input.at<uchar>(y_1, x_2);
                double p3 = input.at<uchar>(y_2, x_1);
                double p4 = input.at<uchar>(y_2, x_2);
                // 计算权重
                double weight_x_2 = x_src - x_1;
                double weight_x_1 = 1 - weight_x_2;
                double weight_y_2 = y_src - y_1;
                double weight_y_1 = 1 - weight_y_2;
                // 首先在 x 方向上对两个像素进行线性插值
                double p_x_1 = weight_x_1 * p1 + weight_x_2 * p2;
                double p_x_2 = weight_x_1 * p3 + weight_x_2 * p4;
                // 然后在 y 方向上对两个插值结果进行线性插值
                double p_dst = weight_y_1 * p_x_1 + weight_y_2 * p_x_2;
                // 赋值
                output.at<uchar>(j, i) = static_cast<unsigned char>(p_dst);
            }
            else if (type == CV_8UC3) {
                // 从输入图像中获取上述四个坐标对应的像素值
                cv::Vec3b p1 = input.at<cv::Vec3b>(y_1, x_1);
                cv::Vec3b p2 = input.at<cv::Vec3b>(y_1, x_2);
                cv::Vec3b p3 = input.at<cv::Vec3b>(y_2, x_1);
                cv::Vec3b p4 = input.at<cv::Vec3b>(y_2, x_2);
                // 计算权重
                double weight_x_2 = x_src - x_1;
                double weight_x_1 = 1 - weight_x_2;
                double weight_y_2 = y_src - y_1;
                double weight_y_1 = 1 - weight_y_2;
                // 首先在 x 方向上对两个像素进行线性插值
                cv::Vec3b p_x_1 = weight_x_1 * p1 + weight_x_2 * p2;
                cv::Vec3b p_x_2 = weight_x_1 * p3 + weight_x_2 * p4;
                // 然后在 y 方向上对两个插值结果进行线性插值
                cv::Vec3b p_dst = weight_y_1 * p_x_1 + weight_y_2 * p_x_2;
                // 赋值
                output.at<cv::Vec3b>(j, i) = p_dst;
            }
        }
    }
}
