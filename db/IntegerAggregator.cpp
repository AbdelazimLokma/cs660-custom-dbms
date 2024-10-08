#include <db/IntegerAggregator.h>
#include <db/IntField.h>
#include <climits>


using namespace db;

class IntegerAggregatorIterator : public DbIterator {
private:
    // TODO pa3.2: some code goes here
    std::unordered_map<Field*, int> count;
    std::unordered_map<Field*, int> groupSum;
    Aggregator::Op what;
    int gbfield;
    std::unordered_map<Field*, int>::iterator current;
    TupleDesc td;

public:
    IntegerAggregatorIterator(int gbfield, const TupleDesc &td, const std::unordered_map<Field *, int> &count, std::unordered_map<Field *, int> &groupSum, Aggregator::Op what)
    : count(count), groupSum(groupSum), what(what), gbfield(gbfield), td(td) {
    }
    // TODO pa3.2: some code goes here


    void open() override {
        // TODO pa3.2: some code goes here
        current = count.begin();
    }

    bool hasNext() override {
        // TODO pa3.2: some code goes here
        return current != count.end();
    }

    Tuple next() override {
        // TODO pa3.2: some code goes here
        if (!hasNext()){
            throw std::runtime_error("No elements left");
        }
        Field* currentKey = current->first;
        int aggregateVal = groupSum[currentKey];
        int countValue = count[currentKey];
        int resultValue = 0;

        switch(what){
            case Aggregator::Op::SUM:
            case Aggregator::Op::MIN:
            case Aggregator::Op::MAX:
                resultValue = aggregateVal;
                break;
            case Aggregator::Op::COUNT:
                resultValue = countValue;
            case Aggregator::Op::AVG:
                if (countValue != 0){
                    resultValue = aggregateVal / countValue;
                }else {
                    resultValue = 0;
                }
        }
        Tuple tuple = Tuple(td, nullptr);
        if(gbfield == -1){
            tuple.setField(0, new IntField(resultValue));
        }else{
            tuple.setField(0, (const IntField*)currentKey);
            tuple.setField(1, new IntField(resultValue));
        }
        current++;
        return tuple;
    }

    void rewind() override {
        // TODO pa3.2: some code goes here
        current = count.begin();
    }

    const TupleDesc &getTupleDesc() const override {
        // TODO pa3.2: some code goes here
        return td;
    }

    void close() override {
        // TODO pa3.2: some code goes here
        current = count.end();
    }
};

IntegerAggregator::IntegerAggregator(int gbfield, std::optional<Types::Type> gbfieldtype, int afield,
                                     Aggregator::Op what) : gbfield(gbfield), gbfieldtype(gbfieldtype), afield(afield), what(what){
    // TODO pa3.2: some code goes here
}

void IntegerAggregator::mergeTupleIntoGroup(Tuple *tup) {
    // TODO pa3.2: some code goes here
//
//    std::unordered_map<Field*, int> count;
//    std::unordered_map<Field*, int> groupSum;
    Field* groupByField = nullptr;
    if(gbfield != NO_GROUPING){
        groupByField = const_cast<Field*>(&tup->getField(gbfield));
    }
    const IntField field = (IntField &) tup->getField(afield);

    if(count.find(groupByField) == count.end()) {
        count[groupByField] = 1; // Initialize count for this group
    } else {
        count[groupByField]++;
    }

    if (groupSum.find(groupByField) == groupSum.end()) {
        groupSum[groupByField] = (what == Op::MIN) ? INT_MAX : 0;
    }
    int tupleValue = ((IntField&)tup->getField(afield)).getValue();
    switch (what) {
        case Op::SUM:
        case Op::AVG:
            groupSum[groupByField] += tupleValue;
            break;
        case Op::MAX:
            if (tupleValue > groupSum[groupByField]) {
                groupSum[groupByField] = tupleValue;
            }
            break;
        case Op::MIN:
            if (tupleValue < groupSum[groupByField]) {
                groupSum[groupByField] = tupleValue;
            }
            break;
        case Op::COUNT:
            break;
    }

}

DbIterator *IntegerAggregator::iterator() const {
    // TODO pa3.2: some code goes here
    auto td = gbfield != NO_GROUPING ? TupleDesc({Types::INT_TYPE, Types::INT_TYPE}, {"groups", "aggregate"}) : TupleDesc({Types::INT_TYPE}, {"aggregate"});
    auto countCopy = count;
    auto groupSumCopy = groupSum;
    return new IntegerAggregatorIterator(gbfield, td, countCopy, groupSumCopy, what);
}