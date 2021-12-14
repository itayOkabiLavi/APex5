/*
 * TimeSeries.h
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
//#include "AnomalyDetector.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

class TimeSeries{
    int colCount;
    int rowCount;
    string *labels;
    // data[i] = row i, data[i][j] = value of (i,j)
    float **values;
public:
    TimeSeries(int newColCount, int newRowCount);

    TimeSeries(int newColCount, int newRowCount, string *newLabels, float **newValues);

    TimeSeries(const char *CSVfileName);

    void setVal(int row, int column, float val);

    void printTable();

    void printLabels();

    float getValue(int r, int c) { return values[r][c]; }

    // return amount of columns in values (labels of table not included)
    int getCCount() { return colCount; }

    // return amount of rows in values (labels of table not included)
    int getRCount() { return rowCount; }
	// return label name by index in labels array
	string getLabelByIndex(int index) { return labels[index]; }
	// return labels array
	string* getLabels() { return labels; }

    void copyColumn(int columnIndex, float *copyTo);

    void copyColumn(const string label, float *copyTo);

    void copyRow(int rowIndex, float *copyTo);

private:
    bool setTableDimentions(string path) {
        rowCount = 0;
        colCount = 0;
        ifstream file(path);
        if (file.good()) {
            string row, val;
            getline(file, row);
            stringstream ss(row);
            while (getline(ss, val, ',')) { ++colCount; }
            while (getline(file, row)) { ++rowCount; }
            file.close();
            return true;
        }
        return false;
    }

    bool setLabels(string path) {
        ifstream file(path);
        if (file.good()) {
            string header;
            labels = new string[colCount];

            getline(file, header);
            stringstream ss(header);
            for (int i = 0; i < colCount; i++) {
                getline(ss, labels[i], ',');
            }
            file.close();
            return true;
        }
        return false;
    }

    bool setValues(string path) {
        float **pp = new float *[rowCount];
        for (int row = 0; row < rowCount; row++) {
            pp[row] = new float[colCount];
        }
        values = pp;
        ifstream file(path);
        if (file.good()) {
            string rowValue, val;
            getline(file, rowValue); //skip first line (labels)

            for (int row = 0; row < rowCount; row++) {
                getline(file, rowValue);
                stringstream ss(rowValue);
                for (int col = 0; col < colCount; col++) {
                    getline(ss, val, ',');
                    values[row][col] = stof(val);
                }
            }
            file.close();
            return true;
        }
        return false;
    }
};

#endif /* TIMESERIES_H_ */
