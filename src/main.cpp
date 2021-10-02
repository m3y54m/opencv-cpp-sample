#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;
using namespace std;

void processImage(uchar *inputImage, uchar *outputImage);

Mat originalImage;
Mat resultImage;

int main()
{
    // Find the path for 'parrot.jpg' image
    string imagePath = samples::findFile("parrot.jpg");

    cout << imagePath << endl;

    // Read 'parrot.jpg' as an OpenCV colored image
    originalImage = imread(imagePath, IMREAD_COLOR);

    // Exception handling
    if (originalImage.empty())
    {
        cout << "Could not read the image: " << imagePath << endl;
        return 2;
    }

    imshow("Original Image", originalImage);

    // The main image processing function
    processImage(originalImage.data, resultImage.data);

    // Wait for a keystroke in the window
    int k = waitKey(0);

    if (k == 's')
    {
        // Save output image
        imwrite("output.jpg", resultImage);
    }

    return 0;
}

void processImage(uchar *inputImage, uchar *outputImage)
{
    resultImage = originalImage.clone();
}