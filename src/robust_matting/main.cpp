#include "robust_matting.h"
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>
#include <exception>
#include <ostream>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <iostream>



typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

using namespace Eigen;

std::vector<std::string> getFilesList(std::string dirpath){
    DIR *dir = opendir(dirpath.c_str());
    if (dir == NULL)
    {
        std::cout << "opendir error" << std::endl;
    }
 
    std::vector<std::string> allPath;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR){//It's dir
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            std::string dirNew = dirpath + "/" + entry->d_name;
            std::vector<std::string> tempPath = getFilesList(dirNew);
            allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());
 
        }else {
            //cout << "name = " << entry->d_name << ", len = " << entry->d_reclen << ", entry->d_type = " << (int)entry->d_type << endl;
            std::string name = entry->d_name;
            std::string imgdir = dirpath +"/"+ name;
            //sprintf("%s",imgdir.c_str());
            allPath.push_back(imgdir);
        }
 
    }
    closedir(dir);
    //system("pause");
    return allPath;
}

void Stringsplit(std::string str, const char split, std::vector<std::string> &res)
{
    std::istringstream iss(str);       // 输入流
    std::string token;                 // 接收缓冲区
    while (getline(iss, token, split)) // 以split为分隔符
    {
        res.push_back(token);
    }
}


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