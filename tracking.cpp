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
/*

int main()
{
    int TOTAL;

    int max_line=0;
    double max_per=0;
    std::string matched_add;
    char data[20], *sp = "\n", *token;
    std::string add, temp;
    int j=0;
    
    clock_t begin = clock();
	// Read input images
	cv::Mat image1= cv::imread("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/IMG0237.jpg",0);    //image1 is picture come from user.
//  cv::Mat image1= cv::imread("canl1.jpg",0);
    cv::Mat image2;
    
    std::vector<cv::KeyPoint> keypoints1;
    
    cv::SurfFeatureDetector surf(3000);
    
    // Detection of the SURF features
    surf.detect(image1,keypoints1);

    // Construction of the SURF descriptor extractor
    cv::SurfDescriptorExtractor surfDesc;
    
    // Extraction of the SURF descriptors
    cv::Mat descriptors1, descriptors2;
    surfDesc.compute(image1,keypoints1,descriptors1);
    
    FILE *filename;
    filename = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/image_file.txt","r");
//  filename = fopen("image_file.txt","r");
    
    while(fgets(data, 20, filename)){
        
        
        
        add ="/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
        
        if(j ==0){
            
            token = strtok(data, sp);
            TOTAL = atoi(token);
            
            j++;
            continue;
        }
        

            
        token = strtok(data,sp);
        
        temp = token;
        
        add = add + temp;
        //add = temp;
        
        image2 = cv::imread(add,0);

    
    
        std::vector<cv::KeyPoint> keypoints2;
        
  
        surf.detect(image2,keypoints2);

        surfDesc.compute(image2,keypoints2,descriptors2);

        std::cout << "descriptor matrix size: " << descriptors1.rows << " by " << descriptors1.cols << std::endl;

        // Construction of the matcher 
        cv::BruteForceMatcher<cv::L2<float> > matcher;

        // Match the two image descriptors
        std::vector<cv::DMatch> matches;
        matcher.match(descriptors1,descriptors2, matches);


        int i, c=0;
        for(i=0; i<matches.size(); i++){
            if(matches[i].distance < 0.2)
                c++;
        }
    
        std::cout << "Line : " << j <<"    "<< "Matched : " << c <<"    "<< "Total : " << i <<std::endl;
        double per=0;
        per = (double)c/(double)i*100;
        
        if(max_per < per){
            max_per = per;
            max_line = j;
            matched_add = add;
        }
        
        std::cout << per << "%" <<std::endl;
        

        j++;
	
    }
    
    std::cout << "Picture line : " << max_line <<"    "<< "Percent : " << max_per <<"    "<< "Picture address : " << matched_add <<std::endl;
    clock_t end = clock();
    double msec = (double)(end - begin) / CLOCKS_PER_SEC;
    
    std::cout<< msec << std::endl;
    
	return 0;
}*/