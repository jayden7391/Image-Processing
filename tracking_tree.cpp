
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
#include "Tree_Header.h"

int count;

void init_node(node *node){
    
    node->leaf = 0;
    node->line = (int*)malloc(sizeof(int)*B);
    int i;
    for(i=0; i<B; i++)
        node->line[i] = 0;
    
    node->n_loc = 0;
    node->c_loc = 0;
    node->n_leaf = 0;
    total_line++;
    node->f_loc = total_line;
    node->centroid_line = 0;
    
};

void make_node(node *nptr){
    
    nptr = (node*)malloc(sizeof(node));
    
    init_node(nptr);
    
};

void read_node(int loc, node *nptr){
    
    int i=1, j, k;
    char data[400];
    char *sp = "_\n", *sp1 = ",";
    char *token, *token1, *token2;
    
    fclose(TREE);
    
    TREE = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/tree", "r");
    
    while(fgets(data, 400, TREE)){
        
        if(i == loc){
            
            token = strtok(data, sp);
            
            for(j=0; j<7; j++){
                
                if(j == 0){
                    nptr->f_loc = atoi(token);
                    token1 = strtok(NULL, sp);
                }
                
                else if(j == 1){
                    nptr->c_loc = atoi(token1);
                    token1 = strtok(NULL, sp);
                }
                
                else if(j == 2){
                    nptr->n_loc = atoi(token1);
                    token1 = strtok(NULL, sp);
                }
                
                else if(j == 3){
                    nptr->n_leaf = atoi(token1);
                    token1 = strtok(NULL, sp);
                }
                
                else if(j == 4){
                    nptr->leaf = atoi(token1);
                    token1 = strtok(NULL, sp);
                }
                
                else if(j == 5){
                    
                    nptr->centroid_line = atoi(token1);
                    token1 = strtok(NULL, sp);
                    
                }
                
                else if(j == 6){
                    
                    token2 = strtok(token1, sp1);
                    
                    for(k=0; k<nptr->n_leaf; k++){
                        
                        nptr->line[k] = atoi(token2);
                        
                        token2 = strtok(NULL, sp1);
                        
                    }
                    
                    for(k=nptr->n_leaf; k<B; k++)
                        nptr->line[k] = 0;
                }
                
            }
            
            break;
            
        }
        
        else{
            i++;
        }
        
    }
    
    fclose(TREE);
    
};

void find_real_pic(node *nptr, std::string add, std::string add1){
    
    
    std::vector<cv::KeyPoint> keypoints1;
    
    cv::SurfDescriptorExtractor surfDesc;
    cv::Mat descriptors1;
    cv::FileStorage fs1(add1,cv::FileStorage::READ);
    cv::FileNode kptFileNode = fs1["test"];
    read(kptFileNode, keypoints1);
    fs1.release();
    cv::Mat image1= cv::imread(add,0);
    
    surfDesc.compute(image1,keypoints1,descriptors1);
    
    
    FILE *f;
    char data[40];
    int i=0, j;
    int temp = 0;
    
    f = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/image_file.txt","r");
    
    for(j=0; j<nptr->n_leaf; j++){
    
        while(fgets(data,40,f)){
        
            if(i == nptr->line[j])
                break;
            else
                i++;
        
        }
    
        char *token, *sp="\n";
    
        token = strtok(data, sp);
    
        std::string address, address1;
    
        address = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
        address = address + token;
        address1 = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/" ;
        address1 = address1 + token + ".txt";
    
        std::vector<cv::KeyPoint> keypoints2;
    
        cv::SurfDescriptorExtractor surfDesc2;
        cv::Mat descriptors2;
        cv::FileStorage fs2(address1,cv::FileStorage::READ);
        cv::FileNode kptFileNode2 = fs2["test"];
        read(kptFileNode2, keypoints2);
        fs2.release();
        cv::Mat image2= cv::imread(address,0);
    
        surfDesc2.compute(image2,keypoints2,descriptors2);
    
    
        // Construction of the matcher
        cv::BruteForceMatcher<cv::L2<float> > matcher;
    
        // Match the two image descriptors
        std::vector<cv::DMatch> matches;
        matcher.match(descriptors1,descriptors2, matches);
    
        int j, c=0;
        for(j=0; j<matches.size(); j++){
            if(matches[j].distance < 0.2)
                c++;
        }
    
        double per=0;
        per = (double)c/(double)j*100;
        
        count ++;
        
        if(per > 50){
            
            printf("Find!!\n");
            printf("%s\n",token);
            printf("%f",per);
            std::cout << "%" << std::endl;
            temp = 1;
            
            
        }
        
        if(temp == 1)
            break;
    }
    
};

void find_next(node *nptr, std::string add, std::string add1){
  
    
    std::vector<cv::KeyPoint> keypoints1;
    
    cv::SurfDescriptorExtractor surfDesc;
    cv::Mat descriptors1;
    cv::FileStorage fs1(add1,cv::FileStorage::READ);
    cv::FileNode kptFileNode = fs1["test"];
    read(kptFileNode, keypoints1);
    fs1.release();
    cv::Mat image1= cv::imread(add,0);
    
    surfDesc.compute(image1,keypoints1,descriptors1);
    
    
    FILE *f;
    char data[40];
    int i=0;
    
    f = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/image_file.txt","r");
    
    while(fgets(data,40,f)){
        
        if(i==0){
            i++;
            continue;
        }
        
        if(i == nptr->centroid_line)
            break;
        else
            i++;
        
    }
    
    char *token, *sp="\n";
    
    token = strtok(data, sp);
    
    std::string address, address1;
    
    address = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
    address = address + token;
    address1 = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/" ;
    address1 = address1 + token + ".txt";
    
    std::vector<cv::KeyPoint> keypoints2;
    
    cv::SurfDescriptorExtractor surfDesc2;
    cv::Mat descriptors2;
    cv::FileStorage fs2(address1,cv::FileStorage::READ);
    cv::FileNode kptFileNode2 = fs2["test"];
    read(kptFileNode2, keypoints2);
    fs2.release();
    cv::Mat image2= cv::imread(address,0);
    
    surfDesc2.compute(image2,keypoints2,descriptors2);
    
    
    // Construction of the matcher
    cv::BruteForceMatcher<cv::L2<float> > matcher;
    
    // Match the two image descriptors
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1,descriptors2, matches);
    
    int j, c=0;
    for(j=0; j<matches.size(); j++){
        if(matches[j].distance < 0.35)
            c++;
    }
    
    double per=0;
    per = (double)c/(double)j*100;

    count ++;
    
    if(per > 70){
        
        if(nptr->leaf == 1){
            
            find_real_pic(nptr, add, add1);
            
        }
        
        else{
            
            read_node(nptr->c_loc, nptr);
            
            find_next(nptr, add, add1);
            
        }
        
    }
    
    else{
        
        if(nptr->f_loc == 1){
            
            read_node(nptr->c_loc, nptr);
            
        }
        else{
            read_node(nptr->n_loc, nptr);
        }
        
        find_next(nptr, add, add1);
        
    }
    
    
};



int main(void){
    std::string matched_add;
    std::string add, add1, add_or, temp, name;
    int j=0;
    
    count = 0;
    
    FILE *tree;
    
    tree = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/tree","r");
    name = "baboon1.jpg";
    add ="/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
    add1 = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/";
    
    add = add + name;
    add1 = add1 + name + ".txt";
    
    

    
    node *nptr;
    
    nptr = (node*)malloc(sizeof(node));
    init_node(nptr);
    
    clock_t begin = clock();
    
    
    if(j==0){
            
        root = (node*)malloc(sizeof(node));
        init_node(root);
        read_node(1, root);
        nptr = root;
        
    }
        
    find_next(nptr, add, add1);

    
    
    clock_t end = clock();
    double msec = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout<< count << "times" << std::endl;
    std::cout<< msec <<"s"<< std::endl;
    
    return 0;
}