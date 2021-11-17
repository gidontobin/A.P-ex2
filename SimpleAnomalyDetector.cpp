
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"
#include <map>
#include <vector>

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	map<string,vector<float>> map_elements = ts.getMap();
	int num_of_keys = ts.size();
	int num_of_rows = ts.length();
	float threshold = 0.9;

	for(map<string,vector<float>>::iterator header : map_elements) {
        float maxCor = 0;
        string corTo = "";

        for (map<string,vector<float>>::iterator next = header+1;next!=map_elements.end();next++) {
            float cor = pearson(header->second,next->second, num_of_rows);
            if(cor<0)
                cor = -cor;

            if (cor > maxCor && cor>=threshold) {
                maxCor = cor;
                corTo = next->first;
            }
        }

        if (corTo=="")
            continue;
        Point points[num_of_rows];

        for(int i=0;i<num_of_rows;i++) {
            points[i] = new Point(header->second[i],map_elements[corTo][i]);
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

        corOfI.feature1 = header->first;
        corOfI.feature2 = corTo;
        corOfI.corrlation = maxDev;
        corOfI.lin_reg = linear_reg;
        corOfI.threshold = threshold;

        this->cf.push_back(corOfI);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> report;
	map<string,vector<float>> map_elements = ts.getMap();

	int num_of_keys = ts.size();
    int num_of_rows = ts.length();

    //check every pair that was found as cor in learnNormal function
    for(correlatedFeatures corOfI : this->cf){

        //make array of points
        Point points[num_of_rows];
        for(int i=0;i<num_of_rows;i++) {
            points[i] = new Point(map_elements[corOfI.feature1][i],map_elements[corOfI.feature2][i]);
        }

        //get worst point
        float maxDev = 0;
        int badIndex = 0;
        for(int i=0;i<num_of_rows;i++) {
            float getDev = dev(points[i],corOfI.lin_reg);
            if(getDev>maxDev){
                maxDev=getDev;
                badIndex = i;
            }
        }

        //check if point is really bad, and if so, add a report to the vector of reports
        if (maxDev>corOfI.corrlation){
            report.push_back(new AnomalyReport(corOfI.feature1+"-"+corOfI.feature2,badIndex));
        }
    }
    return report;
}

