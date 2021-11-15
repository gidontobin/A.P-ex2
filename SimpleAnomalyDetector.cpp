
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

// Yohay The Fox
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	// TODO Auto-generated destructor stub

	float* matrix = ts.getMat();
	int num_of_colums = ts.size();
	int num_of_rows = ts.length();
	float threshold = 0.9;
	for(int i = 0; i<num_of_colums; i++) {
        float maxCor = 0;
        int corTo = -1;

        for (int j = i + 1; j < num_of_colums; j++) {
            float cor = pearson(matrix[1][i], matrix[1][j], num_of_rows);
            if(cor<0)
                cor = -cor;

            if (cor > maxCor && cor>=threshold) {
                maxCor = cor;
                corTo = j;
            }
        }

        if (corTo==-1)
            continue;
        Point points[num_of_rows];
        for(int x = 1; x<num_of_rows; x++) {
            points[x] = new Point(matrix[x][i],matrix[x][corTo]);
        }

        float maxDev = 0;
        Line lin_reg = linear_reg(points,num_of_rows);
        for(int x = 0; x<num_of_rows; x++) {
            float getDev = dev(points[x],lin_reg);
            if(getDev>maxDev)
                maxDev=getDev;
        }

        maxDev=maxDev*1.1;
        correlatedFeatures corOfI;
        corOfI.feature1 = matrix[0][i];
        corOfI.feature2 = matrix[0][corTo];
        corOfI.corrlation = maxDev;
        corOfI.lin_reg = linear_reg;
        corOfI.threshold = threshold;

        this->cf.push_back(corOfI);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
    for(correlatedFeatures corOfI : this->cf){

    }
}

