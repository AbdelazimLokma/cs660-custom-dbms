#include <db/Insert.h>
#include <db/Database.h>
#include <db/IntField.h>

using namespace db;

std::optional<Tuple> Insert::fetchNext() {
    // TODO pa3.3: some code goes here
    int counter = 0;
    BufferPool &bufferpool = Database::getBufferPool();
    while (child->hasNext()) {
        Tuple t = child->next();
        bufferpool.insertTuple(this->t, this->tableId, &t);
        counter++;
    }
    if (counter > 0){
        Tuple newTuple(getTupleDesc());
        newTuple.setField(0, new IntField(counter));
        return newTuple;
    }else{
        return std::nullopt; //TODO: how do we know when to return NULL?
    }
}

Insert::Insert(TransactionId t, DbIterator *child, int tableId) : t(t), child(child), tableId(tableId) {
    // TODO pa3.3: some code goes here
}

const TupleDesc &Insert::getTupleDesc() const {
    // TODO pa3.3: some code goes here
    child->getTupleDesc();
}

void Insert::open() {
    // TODO pa3.3: some code goes here
    child->open();
}

void Insert::close() {
    // TODO pa3.3: some code goes here
    child->close();
}

void Insert::rewind() {
    // TODO pa3.3: some code goes here
    if (!child) {
       // throw std::IllegalStateException; TODO: figure out why this error is not already defined
    }
    child->rewind();
}

std::vector<DbIterator *> Insert::getChildren() {
    // TODO pa3.3: some code goes here
    std::vector<DbIterator *> children; //TODO: understand why we need to get children when we only have one DB iterator
    children.push_back(child); // this confusion also applies to aggregate!
    return children;
}

void Insert::setChildren(std::vector<DbIterator *> children) {
    // TODO pa3.3: some code goes here
    if (!children.empty()) {
        child = children[0];
    }
}
