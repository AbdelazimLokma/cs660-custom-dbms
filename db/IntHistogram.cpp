#include <db/IntHistogram.h>


using namespace db;

IntHistogram::IntHistogram(int buckets, int min, int max): min(min), max(max), totalValues(0) {
    // TODO pa4.1: some code goes here
    this->buckets = std::min(buckets, max - min + 1);
    this->bucketCount.resize(this->buckets, 0);
}

void IntHistogram::addValue(int v) {
    // TODO pa4.1: some code goes here
    int index = (v - min) * buckets / (max - min + 1);
    bucketCount[index]++;
    totalValues++;
}

double IntHistogram::estimateSelectivity(Predicate::Op op, int v) const {
    if (totalValues == 0) return 0.0;

    if (v < min) {
        if (op == Predicate::Op::LESS_THAN || op == Predicate::Op::LESS_THAN_OR_EQ) {
            return 0.0;
        } else {
            return 1.0;
        }
    } else if (v > max) {
        if (op == Predicate::Op::GREATER_THAN || op == Predicate::Op::GREATER_THAN_OR_EQ) {
            return 0.0;
        } else {
            return 1.0;
        }
    }

    int index = std::min(std::max((v - min) * buckets / (max - min + 1), 0), buckets - 1);
    double width = std::max(1.0, static_cast<double>(max - min + 1) / buckets);
    double bucketStart = min + index * width;
    double bucketEnd = bucketStart + width;
    double selectivity = 0.0;

    switch (op) {
        case Predicate::Op::EQUALS:
            if (v < min || v > max) return 0.0;
            selectivity = static_cast<double>(bucketCount[index]) / width / totalValues;
            break;
        case Predicate::Op::NOT_EQUALS:
            if (v < min || v > max) return 1.0;
            selectivity = 1 - static_cast<double>(bucketCount[index]) / width / totalValues;
            break;
        case Predicate::Op::LESS_THAN:
        case Predicate::Op::LESS_THAN_OR_EQ: {
            double bucketFraction = (v - bucketStart) / width;
            if (op == Predicate::Op::LESS_THAN) {
                selectivity += bucketFraction * static_cast<double>(bucketCount[index]) / totalValues;
            } else {
                bucketFraction = (v - bucketStart + 1) / width;
                selectivity += bucketFraction * static_cast<double>(bucketCount[index]) / totalValues;
            }
            for (int i = 0; i < index; i++) {
                selectivity += static_cast<double>(bucketCount[i]) / totalValues;
            }
            break;
        }
        case Predicate::Op::GREATER_THAN:
        case Predicate::Op::GREATER_THAN_OR_EQ: {
            double bucketFraction = (bucketEnd - v - 1) / width;
            if (op == Predicate::Op::GREATER_THAN) {
                selectivity += bucketFraction * static_cast<double>(bucketCount[index]) / totalValues;
            } else {
                bucketFraction = (bucketEnd - v) / width;
                selectivity += bucketFraction * static_cast<double>(bucketCount[index]) / totalValues;
            }
            for (int i = index + 1; i < buckets; i++) {
                selectivity += static_cast<double>(bucketCount[i]) / totalValues;
            }
            break;
        }
    }
    return selectivity;
}


double IntHistogram::avgSelectivity() const {
    // TODO pa4.1: some code goes here
    return 0.0;
}

std::string IntHistogram::to_string() const {
    // TODO pa4.1: some code goes here
    return "hi kostas";
}
