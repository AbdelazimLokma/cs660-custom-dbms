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
    int estimatedCardinality = 0;

    // Check if it's an equality join
    if (joinOp == Predicate::Op::EQUALS) {
        // If one of the attributes is a primary key
        if (t1pkey || t2pkey) {
            estimatedCardinality = std::min(card1, card2);
        } else {
            estimatedCardinality = std::max(card1, card2);
        }
    } else if (joinOp == Predicate::Op::NOT_EQUALS) {
        // Handle NOT_EQUALS differently (you may want to refine this based on your specific requirements)
        estimatedCardinality = std::max(card1, card2);
    } else if (joinOp == Predicate::Op::GREATER_THAN || joinOp == Predicate::Op::LESS_THAN ||
               joinOp == Predicate::Op::LESS_THAN_OR_EQ || joinOp == Predicate::Op::GREATER_THAN_OR_EQ) {
        // Range scans, assume a fixed fraction of the cross-product is emitted (e.g., 30%)
        estimatedCardinality = static_cast<int>(0.3 * card1 * card2);
    } else {
        // Handle other operations (LIKE) accordingly, you may need additional heuristics
        // For simplicity, assume a fixed fraction for unknown operations
        estimatedCardinality = static_cast<int>(0.5 * card1 * card2);
    }

    return estimatedCardinality;
}

std::vector<LogicalJoinNode> JoinOptimizer::orderJoins(std::unordered_map<std::string, TableStats> stats,
                                                       std::unordered_map<std::string, double> filterSelectivities) {
    // TODO pa4.3: some code goes here
}
