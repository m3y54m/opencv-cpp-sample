#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void printImageInfo(Mat inputImage);
void processImageMat(const Mat inputImage, Mat &outputImage);

Mat originalImage;
Mat resultImage;

int main()
{
    // Find the path for 'parrot.jpg' image
    string imagePath = samples::findFile("parrot.jpg");

    // Read 'parrot.jpg' in BGR 8UC3 format
    originalImage = imread(imagePath, IMREAD_COLOR);

    // Exception handling
    if (originalImage.empty())
    {
        cout << "Could not read the image: " << imagePath << endl;
        return -1;
    }

    imshow("Original", originalImage);

    cout << "[ Image Information ]" << endl;
    printImageInfo(originalImage);

    resultImage = originalImage.clone();

    // The main image processing function
    processImageMat(originalImage, resultImage);

    // Save output image
    imshow("Result", resultImage);

    // Wait for a keystroke in the window
    int k = waitKey(0);

    if (k == 's')
    {
        // Save output image
        imwrite("output.jpg", resultImage);
    }

    return 0;
}

void processImageMat(const Mat inputImage, Mat &outputImage)
{
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
}

void printImageInfo(Mat inputImage)
{
    int depth = inputImage.depth();
    string depthString = depthToString(depth);

    cout << "Dimensions: " << inputImage.dims << endl;
    cout << "Size: " << inputImage.cols << " x " << inputImage.rows << endl;
    cout << "Depth: " << depthString << endl;
    cout << "Channels: " << inputImage.channels() << endl;
}