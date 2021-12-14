/*
 * TimeSeries.cpp
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */
#include "timeseries.h"
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

TimeSeries::TimeSeries(int newColCount, int newRowCount) {
    colCount = newColCount;
    rowCount = newRowCount;
    // make space for the table
    float** pp = new float*[newRowCount];
    for (int row = 0; row < newRowCount; row++)
    {
        pp[row] = new float[newColCount];
    }
    values = pp;
}
	
TimeSeries::TimeSeries(int newColCount, int newRowCount, string* newLabels,float** newValues) {
    TimeSeries(newColCount, newRowCount);
    for (int col = 0; col < newColCount; col++)
    {
        labels[col] = newLabels[col];
        for (int row = 0; row < newRowCount; row++)
        {
            values[row][col] = newValues[row][col];
        }
    }
}

TimeSeries::TimeSeries(const char* CSVfileName){
    setTableDimentions(CSVfileName);
    setLabels(CSVfileName);
    setValues(CSVfileName);
}
	
void TimeSeries::setVal(int row, int column, float val) {
    values[row][column] = val;
}

void TimeSeries::printTable() {
    for (int row = 0; row < rowCount; row++)
    {
        for (int col = 0; col < colCount; col++)
        {
            cout << values[row][col] << " , ";
        }
        cout << endl;
    }
}

void TimeSeries::printLabels() {
    for (int i = 0; i < colCount; i++)
    {
        cout << labels[i] << " , ";
    }
    cout << endl;
}

void TimeSeries::copyColumn(int columnIndex, float* copyTo) {
    float result[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        copyTo[i] = values[i][columnIndex];
    }

}
void TimeSeries::copyColumn(const string label, float* copyTo) {
    for (int i = 0; i < colCount; i++)
    {
        if (label == labels[i]) {
            copyColumn(i, copyTo);
            return;
        }
    }
    cout << " ... " << label <<" not found" << endl;
}
void TimeSeries::copyRow(int rowIndex, float* copyTo) {
    for (int i = 0; i < colCount; i++)
    {
        copyTo[i] = values[rowIndex][i];
    }
}