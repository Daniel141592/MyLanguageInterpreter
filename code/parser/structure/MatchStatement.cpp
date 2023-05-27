#include "MatchStatement.h"

MatchStatement::MatchStatement(BlockPtr b) : block(std::move(b)) {

}


const Block::BlockPtr &MatchStatement::getBlock() const {
    return block;
}
