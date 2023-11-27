#include <db/IntegerAggregator.h>
#include <db/IntField.h>


using namespace db;

class IntegerAggregatorIterator : public DbIterator {
private:
    // TODO pa3.2: some code goes here
    std::unordered_map<Field*, int> count = std::unordered_map<Field *, int>();
    std::unordered_map<Field*, int> groupSum = std::unordered_map<Field *, int>();
    Aggregator::Op what;

public:
    IntegerAggregatorIterator(int gbfield, const TupleDesc &td, const std::unordered_map<Field *, int> &count, std::unordered_map<Field *, int> &groupSum, Aggregator::Op what)
    : count(count), groupSum(groupSum), what(what) {
        // Initialization goes here
    }{

        // TODO pa3.2: some code goes here
    }

    void open() override {
        // TODO pa3.2: some code goes here
    }

    bool hasNext() override {
        // TODO pa3.2: some code goes here
    }

    Tuple next() override {
        // TODO pa3.2: some code goes here
    }

    void rewind() override {
        // TODO pa3.2: some code goes here
    }

    const TupleDesc &getTupleDesc() const override {
        // TODO pa3.2: some code goes here
    }

    void close() override {
        // TODO pa3.2: some code goes here
    }
};

IntegerAggregator::IntegerAggregator(int gbfield, std::optional<Types::Type> gbfieldtype, int afield,
                                     Aggregator::Op what) : gbfield(gbfield), gbfieldtype(gbfieldtype), afield(afield), what(what){
    // TODO pa3.2: some code goes here
}

void IntegerAggregator::mergeTupleIntoGroup(Tuple *tup) {
    // TODO pa3.2: some code goes here
    Field* groupValue;
    auto* aggValue = const_cast<Field*>(&tup->getField(afield));
    if (gbfield == -1){
        groupValue = nullptr;


    }
    else{
        groupValue = const_cast<Field*>(&tup->getField(gbfield));
    }


    if (what == Op::MAX){

    }
    else if (what == Op::MIN){

    }
    else{

    }


}

DbIterator *IntegerAggregator::iterator() const {
    // TODO pa3.2: some code goes here
    auto td = gbfield != -1 ? TupleDesc({Types::INT_TYPE, Types::INT_TYPE},{"groups", "aggregate"}) :  TupleDesc({Types::INT_TYPE},{"aggregate"});

}
