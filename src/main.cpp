#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
    std::string image_path = samples::findFile("watch.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window 2", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("watch.png", img);
    }
    return 0;
}