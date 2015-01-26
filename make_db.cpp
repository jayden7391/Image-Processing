/*
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <ctime>

int main(void){
    int TOTAL;
    std::string add, temp, file_add, add1;
    int j=0;
    char data[20], *sp = "\n", *token, *token1;
    cv::Mat image1;
    FILE *filename;
    filename = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/image_file.txt","r");
    //  filename = fopen("image_file.txt","r");
    
    while(fgets(data, 20, filename)){
        
        
        
        add ="/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
        add1 ="/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/";
        
        if(j ==0){
            
            token = strtok(data, sp);
            TOTAL = atoi(token);
            
            j++;
            continue;
        }
    
        
        token = strtok(data,sp);
        //token1 = strtok(token,sp1);
        
        temp = token;
        
        add = add + temp;
        //add = temp;
        
        file_add = add1 + token + ".txt";
        
        image1 = cv::imread(add,0);
    

        std::vector<cv::KeyPoint> keypoints1;

        cv::SurfFeatureDetector surf(3000);

        // Detection of the SURF features
        surf.detect(image1,keypoints1);
        

        cv::FileStorage fs(file_add,cv::FileStorage::WRITE);
        write(fs, "test",keypoints1);
        fs.release();
        
        
        
    }
    
    return 0;
}*/