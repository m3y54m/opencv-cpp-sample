#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void printImageInfo(const string title, const Mat inputImage);
void processImage(int width, int height, int depth, int channels, size_t step, uchar *inputImagePointer, uchar *outputImagePointer);
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
    
    // Show original image
    imshow("Original", originalImage);

    printImageInfo("[ Original Image Information ]", originalImage);

    // Just to allocate memory for 'resultImage' the same size as 'originalImage'
    // this memory space is used by 'processImage' function
    resultImage = originalImage.clone();

    // The main image processing function
    processImage(originalImage.cols, originalImage.rows, originalImage.depth(), originalImage.channels(), originalImage.step, originalImage.data, resultImage.data);
    //processImageMat(originalImage, resultImage);

    // Show result image
    imshow("Result", resultImage);

    // Wait for a keystroke in the window
    int k = waitKey(0);

    if (k == 's')
    {
        // Save result image
        imwrite("result.jpg", resultImage);
    }

    return 0;
}

// https://thecodinginterface.com/blog/opencv-Mat-from-array-and-vector/

void processImage(int width, int height, int depth, int channels, size_t step, uchar *inputImagePointer, uchar *outputImagePointer)
{
    int type = CV_MAKETYPE(depth, channels);

    // Mat (int rows, int cols, int type, uchar *data, size_t step=AUTO_STEP)
    //
    // rows	Number of rows in a 2D array.
    // cols	Number of columns in a 2D array.
    // type	Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices,
    //      or CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX
    //      channels) matrices.
    // data	Pointer to the user data. Matrix constructors that take data and step
    //      parameters do not allocate matrix data. Instead, they just initialize
    //      the matrix header that points to the specified data, which means that
    //      no data is copied. This operation is very efficient and can be used to
    //      process external data using OpenCV functions. The external data is not
    //      automatically deallocated, so you should take care of it.
    // step	Number of bytes each matrix row occupies. The value should include the
    //      padding bytes at the end of each row, if any. If the parameter is
    //      missing (set to AUTO_STEP ), no padding is assumed and the actual step
    //      is calculated as cols*elemSize().
    //      For example, if the matrix type is CV_8UC3 , elemSize() returns
    //      3*sizeof(uchar) or 3.

    // Create a 'new' Mat object using Mat data addressed by 'inputImagePointer'
    Mat temp = Mat(height, width, type, inputImagePointer, step);

    // ------------------------------------------------------
    // Main image processing operations are done here:

    cvtColor(temp, temp, COLOR_BGR2GRAY);

    // ------------------------------------------------------

    // To keep the color space of the output image the same as input (BGR)
    cvtColor(temp, temp, COLOR_GRAY2BGR);
    // Copy data of 'output' Mat to the address of 'outputImagePointer'
    memcpy(outputImagePointer, temp.data, width * height * channels * sizeof(uchar));
}

// http://zafar.cc/2018/3/7/passing-cv-mat-as-argument/

void processImageMat(const Mat inputImage, Mat &outputImage)
{
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
}

void printImageInfo(const string title, const Mat inputImage)
{
    int depth = inputImage.depth();
    string depthString = depthToString(depth);

    cout << "----------------------" << endl;
    cout << title << endl;
    cout << "----------------------" << endl;
    cout << "Dimensions: " << inputImage.dims << endl;
    cout << "Step: " << inputImage.step << endl;
    cout << "Size: " << inputImage.cols << " x " << inputImage.rows << endl;
    cout << "Depth: " << depthString << endl;
    cout << "Channels: " << inputImage.channels() << endl;
}