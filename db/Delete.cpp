#include <db/Delete.h>
#include <db/BufferPool.h>
#include <db/IntField.h>
#include <db/Database.h>

using namespace db;

Delete::Delete(TransactionId t, DbIterator *child) : t(t), child(child) {
    // TODO pa3.3: some code goes here
}

const TupleDesc &Delete::getTupleDesc() const {
    // TODO pa3.3: some code goes here
    child->getTupleDesc();
}

void Delete::open() {
    // TODO pa3.3: some code goes here
    child->open();
}

void Delete::close() {
    // TODO pa3.3: some code goes here
    child->close();
}

void Delete::rewind() {
    // TODO pa3.3: some code goes here
    if(!child){
        throw; //Illegal State exception;
    }
    child->rewind();
}

std::vector<DbIterator *> Delete::getChildren() {
    // TODO pa3.3: some code goes here
    std::vector<DbIterator *> children;
    children.push_back(child);
    return children;
}

void Delete::setChildren(std::vector<DbIterator *> children) {
    // TODO pa3.3: some code goes here
    if (!children.empty()) {
        child = children[0];
    }
}

std::optional<Tuple> Delete::fetchNext() {
    // TODO pa3.3: some code goes here
    BufferPool &bufferpool = Database::getBufferPool();
    int deleteCount = 0;
    while(child->hasNext()){
        Tuple currTuple = child->next();
        bufferpool.deleteTuple(t, &currTuple);
        deleteCount++;
    }
    if (deleteCount > 0){
        Tuple newTuple(getTupleDesc());
        newTuple.setField(0, new IntField(deleteCount));
        return newTuple;
    }else{
        return std::nullopt;
    }
}
