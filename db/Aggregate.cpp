#include <db/Aggregate.h>
#include <db/IntegerAggregator.h>
#include <db/StringAggregator.h>

using namespace db;

std::optional<Tuple> Aggregate::fetchNext() {
    // TODO pa3.2: some code goes here
    if (!child->hasNext()) {
        return std::nullopt;
    }
    while(child->hasNext()){
        Tuple nextTuple = child->next();
        agg.mergeTupleIntoGroup(&nextTuple);
    }
    DbIterator *aggIterator = agg.iterator();
    aggIterator->open();
    if (!aggIterator->hasNext()) {
        aggIterator->close();
        return std::nullopt;
    }
    Tuple result = aggIterator->next();
    aggIterator->close();
    return result;
}

Aggregate::Aggregate(DbIterator *child, int afield, int gfield, Aggregator::Op aop): child(child), afield(afield), gfield(gfield), aop(aop), agg(gfield, std::nullopt, afield, aop) {
    // TODO pa3.2: some code goes here
}

int Aggregate::groupField() {
    // TODO pa3.2: some code goes here
    if (gfield == -1){
        return Aggregator::NO_GROUPING;
    }
    return gfield; 
}

std::string Aggregate::groupFieldName() {
    // TODO pa3.2: some code goes here
    if (gfield == -1){
        return nullptr;
    }
    return child->getTupleDesc().getFieldName(gfield);
}

int Aggregate::aggregateField() {
    // TODO pa3.2: some code goes here
    return afield;
}

std::string Aggregate::aggregateFieldName() {
    // TODO pa3.2: some code goes here
    return child->getTupleDesc().getFieldName(afield);
}

Aggregator::Op Aggregate::aggregateOp() {
    // TODO pa3.2: some code goes here
    return aop;
}

void Aggregate::open() {
    // TODO pa3.2: some code goes here
    Operator::open();
    child->open();
}

void Aggregate::rewind() {
    // TODO pa3.2: some code goes here
    Operator::rewind();
    child->rewind();
}

const TupleDesc &Aggregate::getTupleDesc() const {
    // TODO pa3.2: some code goes here
    if (gfield == -1){
        TupleDesc td = TupleDesc({child->getTupleDesc().getFieldType(afield)}, {child->getTupleDesc().getFieldName(afield)});
        return td;
    }
    else{
        TupleDesc td = TupleDesc({child->getTupleDesc().getFieldType(gfield),child->getTupleDesc().getFieldType(afield)}, {child->getTupleDesc().getFieldName(gfield),child->getTupleDesc().getFieldName(afield)});
        return td;
    }

}

void Aggregate::close() {
    // TODO pa3.2: some code goes here
    Operator::close();
    child->close();
}

std::vector<DbIterator *> Aggregate::getChildren() {
    // TODO pa3.2: some code goes here
    return {child};
}

void Aggregate::setChildren(std::vector<DbIterator *> children) {
    // TODO pa3.2: some code goes here
    if (!children.empty()) {
        child = children[0];
    }
}
