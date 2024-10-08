#include <db/JoinOptimizer.h>
#include <db/PlanCache.h>
#include <cfloat>

using namespace db;

double JoinOptimizer::estimateJoinCost(int card1, int card2, double cost1, double cost2) {
    // TODO pa4.2: some code goes here
    double read1 = cost1;
    double read2 = card1 * cost2;
    double cpuCost = static_cast<double>(card1) * card2;
    return read1 + read2 + cpuCost;
}

int JoinOptimizer::estimateTableJoinCardinality(Predicate::Op joinOp,
                                                const std::string &table1Alias, const std::string &table2Alias,
                                                const std::string &field1PureName, const std::string &field2PureName,
                                                int card1, int card2, bool t1pkey, bool t2pkey,
                                                const std::unordered_map<std::string, TableStats> &stats,
                                                const std::unordered_map<std::string, int> &tableAliasToId) {
    // TODO pa4.2: some code goes here
    if(joinOp == Predicate::Op::EQUALS){
        if (t1pkey && t2pkey){
            return std::min(card1, card2);
        }else if(t1pkey){
            return card2;
        }else{
            return card1;
        }
    }else{
        return int(card1 * card2 * 0.3);
    }
}

std::vector<LogicalJoinNode> JoinOptimizer::orderJoins(std::unordered_map<std::string, TableStats> stats,
                                                       std::unordered_map<std::string, double> filterSelectivities) {
    // TODO pa4.3: some code goes here
    
}
