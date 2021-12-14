/*
 * SimpleAnomalyDetector.h
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "timeseries.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>





struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle circle;
    bool fromLinear;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    void setNormalModel(vector<correlatedFeatures> cf) {
        this->cf = cf;
    }
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
    float** getPontsFromTs(TimeSeries ts, int f1, int f2);
};



#endif /* SIMPLEANOMALYDETECTOR_H_ */