#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QApplication>

using namespace cv;

void Demo_draw()
{
    Mat img = Mat::zeros(Size(500,500), CV_8UC3);

    const int size = 5;

    Point points[1][size];

    line(img, Point(3, 4), Point(100, 220), Scalar(0, 255, 0), 2, LINE_8);
    imshow("draw test", img);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    Demo_draw();
    w.show();
    return a.exec();
}
