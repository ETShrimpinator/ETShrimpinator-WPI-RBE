#pragma once

#include <Arduino.h>

class Filter
{
    // an array of the last FILTER_SIZE data points; this will be used as a circular buffer
    // with the index being updated for each new data point, until it rolls over
    std::vector<float> data;
    const int dataSize;

    uint8_t filterIndex = 0;

public:
    Filter(int size) : dataSize(size) {data.resize(dataSize);}

    void addDatum(float value);
    float addAndReturnAverage(float value);
    float addAndReturnMedian(float value);
};