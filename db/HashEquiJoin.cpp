#include <db/HashEquiJoin.h>

using namespace db;

HashEquiJoin::HashEquiJoin(JoinPredicate p, DbIterator *child1, DbIterator *child2): p(p), child1(child1), child2(child2) {
    // TODO pa3.1: some code goes here
    td = TupleDesc::merge(child1->getTupleDesc(), child2->getTupleDesc());
}

JoinPredicate *HashEquiJoin::getJoinPredicate() {
    // TODO pa3.1: some code goes here
    return &this->p;
}

const TupleDesc &HashEquiJoin::getTupleDesc() const {
    // TODO pa3.1: some code goes here
    return td;
}

std::string HashEquiJoin::getJoinField1Name() {
    // TODO pa3.1: some code goes here
    return child1->getTupleDesc().getFieldName(p.getField1());
}

std::string HashEquiJoin::getJoinField2Name() {
    // TODO pa3.1: some code goes here
    return child2->getTupleDesc().getFieldName(p.getField2());

}

void HashEquiJoin::open() {
    // TODO pa3.1: some code goes here
    child1->open();
    child2->open();
}

void HashEquiJoin::close() {
    // TODO pa3.1: some code goes here
    child1->close(); 
    child2->close();
}

void HashEquiJoin::rewind() {
    // TODO pa3.1: some code goes here
    child1->rewind(); 
    child2->rewind();
}

std::vector<DbIterator *> HashEquiJoin::getChildren() {
    // TODO pa3.1: some code goes here
    return {child1, child2};
}

void HashEquiJoin::setChildren(std::vector<DbIterator *> children) {
    // TODO pa3.1: some code goes here
    child1 = children[0]; 
    child2 = children[1]; 
}

std::optional<Tuple> HashEquiJoin::fetchNext() {
    // TODO pa3.1: some code goes here
    while (t1 != std::nullopt || child1->hasNext()) {

        if (t1 == std::nullopt) {
            t1 = child1->next();
        }

        while (child2->hasNext()) {
            Tuple t2 = child2->next();
            if (p.filter(&t1.value(), &t2)) {
                Tuple newTuple = Tuple(td, nullptr);  //Still need to include recordID
                for(auto i = 0; i < t1->getTupleDesc().numFields(); i++){
                    newTuple.setField(i, &t1->getField(i));
                }
                for(auto i = 0; i < t2.getTupleDesc().numFields(); i++){
                    newTuple.setField(t1->getTupleDesc().numFields() + i, &t2.getField(i));
                }
                return newTuple;
            }
        }
        child2->rewind();
        t1 = std::nullopt;
    }
    return std::nullopt;
}
