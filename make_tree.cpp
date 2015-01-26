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
#include "Tree_Header.h"
#include <string.h>
#include <stdio.h>

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
    char *token, *token1, *token2, *token3;
    
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

void write_node(node *nptr){
  
    char s[400];
    int i=1, j;
    FILE *temp;
    int check=0;
    
    temp = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/temp","w");
    TREE = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/tree", "r");
    
    while(fgets(s,400,TREE)){
        
        if(i == nptr->f_loc){
            
            fprintf(temp, "%d_%d_%d_%d_%d_%d_",nptr->f_loc,nptr->c_loc,nptr->n_loc,nptr->n_leaf,nptr->leaf,nptr->centroid_line);
            
            for(j=0; j<B; j++){
                
                if(j < B-1)
                    fprintf(temp,"%d,",nptr->line[j]);
                else
                    fprintf(temp,"%d\n",nptr->line[j]);
            }
            
            
            i++;
        }
        
        else{
            fprintf(temp,"%s",s);
            i++;
        }
        
        check = 1;
    }
    
    if(i == nptr->f_loc){
        fprintf(temp, "%d_%d_%d_%d_%d_%d_",nptr->f_loc,nptr->c_loc,nptr->n_loc,nptr->n_leaf,nptr->leaf,nptr->centroid_line);
        for(j=0; j<B; j++){
            
            if(j < B-1)
                fprintf(temp,"%d,",nptr->line[j]);
            else
                fprintf(temp,"%d\n",nptr->line[j]);
        }
    }
    
    if(check == 0){
        
        fprintf(temp, "%d_%d_%d_%d_%d_%d_",nptr->f_loc,nptr->c_loc,nptr->n_loc,nptr->n_leaf,nptr->leaf,nptr->centroid_line);
        
        for(j=0; j<B; j++){
            
            if(j < B-1)
                fprintf(temp,"%d,",nptr->line[j]);
            else
                fprintf(temp,"%d\n",nptr->line[j]);
        }
        
        
        
        
    }
    
    fclose(TREE);
    fclose(temp);
    
    temp = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/temp", "r");
    TREE = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/tree","w");
    
    while(fgets(s,400,temp)){
        fprintf(TREE,"%s",s);
    }
    
    fclose(TREE);
    fclose(temp);
    
};

void make_db(std::string add, std::string file_add){
    
    
    cv::Mat image1 = cv::imread(add,0);
    
    
    std::vector<cv::KeyPoint> keypoints1;
    
    cv::SurfFeatureDetector surf(3000);
    
    // Detection of the SURF features
    surf.detect(image1,keypoints1);
    
    
    cv::FileStorage fs(file_add,cv::FileStorage::WRITE);
    write(fs, "test",keypoints1);
    fs.release();

    
};

node *split(node *ptr){
    
    node *nptr1, *nptr2;
    
    nptr1 = (node*)malloc(sizeof(nptr1));
    init_node(nptr1);
    nptr2 = (node*)malloc(sizeof(nptr2));
    init_node(nptr2);
    
    nptr1->leaf = 1;
    nptr2->leaf = 1;
    ptr->leaf = 0;
    ptr->n_leaf = 0;
    ptr->c_loc = nptr1->f_loc;
    nptr1->n_loc = nptr2->f_loc;
    
    int i=0, j=0, k=0;
    
    for(i=0; i<B; i++){
        
        if(i%2 == 1){
            if(i == 1)
                nptr1->centroid_line = ptr->line[i];
            nptr1->line[j] = ptr->line[i];
            ptr->line[i] = 0;
            
            if(nptr1->line[j] != 0)
                nptr1->n_leaf++;
            j++;
        }
        else{
            if(i==0)
                nptr2->centroid_line = ptr->line[i];
            nptr2->line[k] = ptr->line[i];
            ptr->line[i] = 0;
            
            if(nptr2->line[j] != 0)
                nptr2->n_leaf++;
            k++;
        }
        
    }
    
    write_node(ptr);
    write_node(nptr1);
    write_node(nptr2);
    
    return nptr1;
};


int find_next(node *ptr, std::string add, std::string add1, int l){
    
    int n, i = 0;
    char data[40], *name, *sp="\n";
    FILE *f;
    std::string address, address1;
    
    f = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/image_file.txt","r");
    
    
    std::vector<cv::KeyPoint> keypoints1;
    cv::SurfDescriptorExtractor surfDesc;
    
    cv::Mat descriptors1;
    cv::FileStorage fs1(add1,cv::FileStorage::READ);
    cv::FileNode kptFileNode1 = fs1["test"];
    read(kptFileNode1, keypoints1);
    fs1.release();
    
    
    
    cv::Mat image1= cv::imread(add,0);
    
    surfDesc.compute(image1,keypoints1,descriptors1);
    
    if(ptr->centroid_line == 0 && ptr->leaf == 1){
        ptr->line[ptr->n_leaf] = l;
        ptr->centroid_line = l;
        ptr->n_leaf ++;
        write_node(ptr);
        return 0;
    }
    
    
    
    n = ptr->centroid_line;
    
    while(fgets(data, 40, f)){
        
        if(i == 0){
            i++;
            continue;
            
        }
        
        if(i == n){
            
            name = strtok(data, sp);
            address = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
            address = address + name;
            address1 = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/";
            address1 = address1 + name + ".txt";
            
            break;
        }
        
        else
            i++;
        
    }
    
    
    std::vector<cv::KeyPoint> keypoints2;
    cv::Mat descriptors2;
    cv::FileStorage fs2(address1,cv::FileStorage::READ);
    cv::FileNode kptFileNode2 = fs2["test"];
    read(kptFileNode2, keypoints2);
    fs2.release();
    
    cv::Mat image2= cv::imread(address,0);
    
    surfDesc.compute(image2,keypoints2,descriptors2);
    
    
    // Construction of the matcher
    cv::BruteForceMatcher<cv::L2<float> > matcher;
    
    // Match the two image descriptors
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1,descriptors2, matches);
    
    int j, c=0;
    for(j=0; j<matches.size(); j++){
        if(matches[j].distance < T)
            c++;
    }
    
    double per=0;
    per = (double)c/(double)j*100;
    
    if(per > 70){
        
        if(ptr->leaf == 1){
            
            if(ptr->n_leaf == B-1){
                ptr = split(ptr);
            }
            
            
            
            ptr->line[ptr->n_leaf] = l;
            ptr->n_leaf ++;
            write_node(ptr);
        }
        
        else{
            
            read_node(ptr->c_loc, ptr);
            
            find_next(ptr, add, add1, l);
        }
        
    }
    
    else{
        
        if(ptr->n_loc != 0){
            read_node(ptr->n_loc, ptr);
            find_next(ptr, add, add1, l);
        }
        
        
        else{
            
            if(ptr->f_loc == 1 && ptr->leaf == 1){
                ptr = split(ptr);
                ptr->line[ptr->n_leaf] = l;
                ptr->centroid_line = l;
                ptr->n_leaf ++;
                write_node(ptr);
                return 0;
            }
            
        
                        
            if(ptr->leaf == 1){
                
                node *new_ptr;
                new_ptr = (node*)malloc(sizeof(node));
                init_node(new_ptr);
                ptr->n_loc = new_ptr->f_loc;
                write_node(ptr);
                ptr = new_ptr;
                ptr->leaf = 1;

                
                if(ptr->n_leaf == B-1){
                    ptr = split(ptr);
                }
                
                
                
                ptr->line[ptr->n_leaf] = l;
                ptr->n_leaf ++;
                write_node(ptr);
            }
            
            else{
                
                read_node(ptr->c_loc, ptr);
                
                find_next(ptr, add, add1, l);

            }

            
        }
                
    }
    
    return 0;
    
};


int main()
{
    
    int TOTAL, TOTAL1;
    int max_line=0;
    double max_per=0, average_dis=0;
    std::string matched_add, new_img, file_add;
    char data[20], data1[20], *sp = "\n", *sp1="_\n", *token, *token1;
    std::string add, add1, add_or, temp;
    int j=0, k, t=0, total_points=0, n=0;
    int check=0;
    T = 0.33;
    B = 32;
    total_line = 0;
    m_p = 0;
    
    db = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/image_file.txt","r");
    TREE = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/tree","r+");
    
    if(TREE == NULL){
        TREE = fopen("/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/tree","w");
        TOTAL1 = 0;
    
    }
    else{
        TOTAL1 = 1;
    }
    
    new_img = "iPhone5.png";
    
    add ="/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
    add1 = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/";
    
    add = add + new_img;
    add1 = add1 + new_img;
    
    cv::Mat image1= cv::imread(add,0);;
    
    std::vector<cv::KeyPoint> keypoints1;
    
    cv::SurfFeatureDetector surf(3000);
    
    // Detection of the SURF features
    surf.detect(image1,keypoints1);

    // Construction of the SURF descriptor extractor
    cv::SurfDescriptorExtractor surfDesc;
    
    // Extraction of the SURF descriptors
    cv::Mat descriptors1, descriptors2;

    surfDesc.compute(image1,keypoints1,descriptors1);
    
    file_add = add1 + new_img + ".txt";
    
    cv::FileStorage fs(file_add,cv::FileStorage::WRITE);
    write(fs, "test",keypoints1);
    fs.release();
    
    
    while(fgets(data, 20, db)){
        
        printf("%d\n", check);
        
        
        
        add ="/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/images/";
        add1 = "/Users/JAYDEN/Jayden/Samsung SDS sGen/2nd/sGen_2nd/sGen_2nd/db/";
        
        if(j ==0){
            
            token = strtok(data, sp);
            TOTAL = atoi(token);
            
            j++;
            
            continue;
        }
        
        if(TOTAL1 == 0){
            
            root = (node*)malloc(sizeof(node));
            
            init_node(root);
            root->f_loc = 1;
            root->leaf = 1;
            root->line[0] = j;
            root->n_leaf = 1;
            root->centroid_line = 1;
            write_node(root);
            
            token = strtok(data,sp);
            
            temp = token;
            
            add = add + temp;
            add1 = add1 + temp + ".txt";
            
            make_db(add, add1);
            TOTAL1 ++;
        }
        
        else{
                
            if(root == NULL){
                
                root = (node*)malloc(sizeof(node));
                init_node(root);
                
                read_node(1, root);
            
            }
            
            
            
            token = strtok(data,sp);
            
            temp = token;
            add = add + temp;
            add1 = add1 + temp + ".txt";
            
            read_node(1, root);
            
            find_next(root, add, add1, j);
            
            
        }
        
        j ++;
        check ++;
    }
    
	return 0;
}*/