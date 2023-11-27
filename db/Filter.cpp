#include <db/Filter.h>
#include "db/DbFile.h"
#include "db/Database.h"

using namespace db;

Filter::Filter(Predicate p, DbIterator *child) : p(p), child(child) {
    // TODO pa3.1: some code goes here
    
}

Predicate *Filter::getPredicate() {
    // TODO pa3.1: some code goes here
     return &p; 
}

const TupleDesc &Filter::getTupleDesc() const {
    // TODO pa3.1: some code goes here
    return child->getTupleDesc(); 
}

void Filter::open() {
    // TODO pa3.1: some code goes here
    Operator::open();
    child->open();
}

void Filter::close() {
    // TODO pa3.1: some code goes here
    Operator::close();
    child->close();
}

void Filter::rewind() {
    // TODO pa3.1: some code goes here
    Operator::rewind();
    child->rewind();
}

std::vector<DbIterator *> Filter::getChildren() {
    // TODO pa3.1: some code goes here
    //unsure about correctness 
    return {child};
}

void Filter::setChildren(std::vector<DbIterator *> children) {
    // TODO pa3.1: some code goes here
    //unsures about correctness
    if (!children.empty()){
        child = children[0];
    }
}

std::optional<Tuple> Filter::fetchNext() {
    // TODO pa3.1: some code goes here
    while(child->hasNext()) {
        Tuple tuple = child->next();
        if (p.filter(tuple)) {
            return tuple;
        }
    }
    return std::nullopt;
}
