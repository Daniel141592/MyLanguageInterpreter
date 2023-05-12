#include "MatchStatement.h"

MatchStatement::MatchStatement(Block b) : block(std::move(b)) {

}


const Block &MatchStatement::getBlock() const {
    return block;
}
