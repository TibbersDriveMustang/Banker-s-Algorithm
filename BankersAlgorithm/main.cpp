//
//  main.cpp
//  Banker`s Algorithm
//
//  Created by Hongyi Guo on 9/25/15.
//  Copyright © 2015 Hongyi Guo. All rights reserved.
//


/*
 Data Structure And Variables Needed:
    MAX:    how much of each resource each process could possibly request
    ALLOCATED:  how much of each resource each process is currently holding
    AVAILABLE:  how much of each resource each process currently has available
 
 
    MAX[][]:    defines the maximum demand of each process.E.g. if MAX[i][j] = k,then Pi may request at most k instances of resource type j
    
    Available[]:    indicates the number of available resources of each type.
    
    Allocation[][]: defines the number of resources of each type currently allocated to each process.E.g. Allocation[i][j] = k,then Process i is currently allocated k instances of resource type j
 
    Need[][]:   Indicates the remaining resource need of each process.E.g. Need[i][j] = k,then Pi may need k more instances of resource type j
 
    Need[i][j] = MAX[i][j] - Allocation[i][j]
 */





//Program to implement Banker`s Algorithm

#include <iostream>
#include <stdio.h>

using namespace std;

int curr[5][5],avl[5];      //Current using resources and current available resources
int maxclaim[5][5];    //Maximum resources needed for each process
int alloc[5] = {0,0,0,0,0};
int maxres[5];          //Maximum resources
int running[5],safeSymbol = 0;
int count_1,i,j,exec,numResources,numProcess,k = 1;

int main(int argc, const char * argv[]) {
    printf("\nEnter the number of processes: ");
    scanf("%d",&numProcess);
    
    for(i = 0;i < numProcess;i++){
        running[i] = 1;
        count_1++;
    }
    
    printf("\nEnter how many kind of resources: ");
    scanf("%d",&numResources);
    

    for(i = 0;i < numResources;i++){
        printf("\n Number of Resource for type %d\n",i+1);
        scanf("%d",&maxres[i]);
    }
    
    printf("\nEnter Current Allocated Resource Table:\n");
    for(i = 0;i < numProcess;i++){
        for(j = 0;j < numResources;j++){
            scanf("%d",&curr[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\nEnter the Maximum Claim Table:\n");
    for(i = 0;i < numProcess;i++){
        for(j = 0;j < numResources;j++){
            scanf("%d",&maxclaim[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\nThe Claim Vector is : ");
    for (i = 0; i < numResources; i++) {
        printf("\t%d",maxres[i]);
    }
    
    printf("\nThe Allocated Resource Table:\n");
    for (i = 0; i < numProcess; i++) {
        for (j = 0; j < numResources; j++){
            printf("\t%d", curr[i][j]);
        }
        printf("\n");
    }
    
    
    printf("\nThe Maximum Claim Table:\n");
    for (i = 0; i < numProcess; i++) {
        for (j = 0; j < numResources; j++)
        {
            printf("\t%d", maxclaim[i][j]);
        }
        printf("\n"); }
    
    //Make Accumulated Allocated Table
    for(i = 0;i < numProcess;i++){
        for(j = 0;j < numResources;j++){
            alloc[j] += curr[i][j];
        }
    }
    
    printf("\nAllocated Resources:");
    for (i = 0; i < numResources; i++) {
        printf("\t%d",alloc[i]);
    }
    
    for (i = 0; i < numResources; i++) {
        avl[i] = maxres[i] - alloc[i];
    }
    
    printf("\nAvailable Resources:");
    for (i = 0; i < numResources; i++) {
        printf("\t%d",avl[i]);
    }
    printf("\n");
    
    
    //Main procedure goes below to check for unsafe state.
    while (count_1 != 0) {
        safeSymbol = 0;
        for (i = 0; i < numProcess; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < numResources; j++) {
                    if(maxclaim[i][j] - curr[i][j] > avl[j]){
                        exec = 0;
                        break;
                    }
                }
                if(exec){
                    printf("\nProcess%d is executing\n",i+1);
                    running[i] = 0;
                    count_1--;
                    safeSymbol = 1;
                    
                    for (j = 0; j < numResources; j++) {
                        avl[j] += curr[i][j];
                    }
                    break;
                }
            }
        }
        if(!safeSymbol){
            printf("\nThe processes are in unsafe state.\n");
            break;
        }
        else{
            printf("\nThe process is in safe state");
            printf("\nAvailable vector:");
            
            for (i = 0; i < numResources; i++) {
                printf("\t%d",avl[i]);
            }
            
            printf("\n");
        }
    }

}




/*SAMPLE OUTPUT -----------------
 Enter the number of processes:5
 Enter the number of resources:4 Enter Claim Vector:8 5 9 7
 Enter Allocated Resource Table: 
 2011
 0121
 4003
 0210 1030
 Enter Maximum Claim Table: 
 3214
 0252
 5105
 1530 
 3033
 The Claim Vector is:
 The Allocated Resource Table:
 2011 0121 4003 0210 1030
 The MaximumClaimTable: 3214
 0252 5105 1530 3033
 Allocated resources: 7 3 Available resources: 1 2
 Process3 is executing
 The process is in safe state
 Available vector: 5 2 Process1 is executing
 The process is in safe state
 Available vector: 7 2 Process2 is executing
 The process is in safe state
 Available vector: 7 3 Process4 is executing
 The process is in safe state
 Available vector: 7 5 Process5 is executing
 The process is in safe state Available vector: 8 5
 7 5 2 2
 2 5
 3 6
 5 7
 6 7
 9 7 
 ---------------------------------------------------------*/