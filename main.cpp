//
// Created by Toshiba on 11/15/2021.
//

#include <iostream>
#include <vector>
#include "AnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

using namespace std;

// this is a simple test to put you on the right track
void generateTrainCSV(float a1,float b1, float a2, float b2){
    ofstream out("trainFile1.csv");
    out<<"A,B,C,D"<<endl;
    Line ac(a1,b1);
    Line bd(a2,b2);
    for(int i=1;i<=100;i++){
        float a=i;
        float b=rand()%40;
        out<<a<<","<<b<<","<<ac.f(a)-0.02+(rand()%40)/100.0f<<","<<bd.f(b)-0.02+(rand()%40)/100.0f<<endl;
    }
    out.close();
}

int main(){
    generateTrainCSV(1,2,3,4);
}