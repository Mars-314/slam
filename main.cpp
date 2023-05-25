#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <iostream>

using namespace std;
using namespace cv;

/*函数作用：视差图转深度图输入：　dispMap ----视差图，8位单通道，CV_8UC1　　K       ----内参矩阵，float类型输出：　　depthMap ----深度图，16位无符号单通道，CV_16UC1*/

void disp2Depth(cv::Mat dispMap, cv::Mat &depthMap, cv::Mat K)
{
    int type = dispMap.type();
    float fx = 718.856 , fy = 718.856, cx = 607.1928, cy = 185.2157;
    float baseline =  573; //基线距离
    if (type == CV_8U)
    {
        /*const float PI = 3.14159265358;*/
        int height = dispMap.rows;
        int width = dispMap.cols;
        uchar* dispData = (uchar*)dispMap.data;
        ushort* depthData = (ushort*)depthMap.data;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int id = i * width + j;
                if (!dispData[id])
                {
                    //防止0除
                    //depthData[id] = 255;
                    continue;
                }
                else
                    depthData[id] = fx * baseline / float(dispData[id]);
            }
        }
    }
    else
    {
        cout << "please confirm dispImg's type!" << endl;
        cv::waitKey(0);
    }
}


int main()
{
    Mat disp8 = imread("/home/mars/Slam/长江项目/深度图/disp2Depth/displeft.png", 0);
    Mat depth(disp8.rows, disp8.cols, CV_16UC1);
    Mat K = (Mat_<float>(3, 3) << 5.8366697641288249e+02, 0., 3.2762020192177897e+02, 0.,				5.3773947573643704e+02, 2.4134709536899661e+02, 0., 0., 1.);
    cout<<K;
    namedWindow("disp", 1);
    imshow("disp", disp8);
    disp2Depth(disp8, depth, K);
    namedWindow("depth", 1);
    imshow("depth", depth);
    imwrite("depth.png", depth);
    waitKey();	cvDestroyAllWindows();
    return 0;
}