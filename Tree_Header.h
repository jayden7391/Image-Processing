//
//  Tree_Header.h
//  sGen_2nd
//
//  Created by Jayden Sehee Lee on 8/18/13.
//  Copyright (c) 2013 Jayden Lee. All rights reserved.
//

#ifndef sGen_2nd_Tree_Header_h
#define sGen_2nd_Tree_Header_h


typedef struct _node{
    
    int f_loc;
    int c_loc;
    int n_loc;
    int leaf;
    int *line;
    int centroid_line;
    int n_leaf;
    
}node;

int total_line;
node *root;
double m_p, T;
int B;
FILE *TREE, *db;

#endif
