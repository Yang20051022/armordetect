#include <opencv2/opencv.hpp>

//杨宇鹏
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  

    // 打开视频文件
    VideoCapture cap;
   cap.open("test3.mp4");

    Mat frame, hsv, mask, result;
    while (true) {
        // 读取新的帧
        cap >>frame;
        if (frame.empty()) break;

        // 转换到HSV颜色空间
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // 设置装甲板的颜色阈值（这里需要根据实际情况调整）
        Scalar lowerBound(0, 50, 50);
        Scalar upperBound(10, 255, 255);
        inRange(hsv, lowerBound, upperBound, mask);

        // 寻找轮廓
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 绘制矩形框
        for (size_t i = 0; i < contours.size(); i++) {
            Rect rect = boundingRect(contours[i]);
            if (rect.area() > 1000) { // 可以设置一个面积阈值来过滤小的噪声
                rectangle(frame, rect, Scalar(0, 255, 0), 2, 8, 0);
            }
        }

        // 显示结果
        imshow("Frame", frame);
        

        // 按'q'退出
        if (waitKey(30) == 'q') break;
    }

    // 释放资源
    cap.release();
    destroyAllWindows();

    return 0;
}