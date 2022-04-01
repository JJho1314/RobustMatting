#include "robust_matting.h"
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>
#include <exception>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace Eigen;

int main(int argc, char** argv)
{

    std::string img_filename = "../data/baby/3.png";
    std::string trimap_filename = "../data/trimaps_0.6/3.png";
    std::string output_filename = "../data/baby/out_3.1.png";
    cv::Mat img = cv::imread(img_filename, cv::IMREAD_COLOR);
    cv::Mat trimap = cv::imread(trimap_filename, cv::IMREAD_GRAYSCALE);

    RobustMatting rm(img, trimap);
    rm.Run();

    cv::Mat rst = rm.GetFinalMat();
    cv::imwrite(output_filename, rst);

    return 0;
}