#ifndef CPP_EVA_TRANSFORMER_H
#define CPP_EVA_TRANSFORMER_H

#include "expressions.h"
#include "memory"

class Transformer {
public:
    auto transformForToWhile(ExpressionPtr forLoop) {
//        auto loop = dynamic_cast<Loop*>(forLoop.get());
//        auto condition = std::move(loop->condition);
//        auto body = std::move(loop->body);
//
//        auto whileBody = Block::create({
//            std::move(body),
//            std::move(loop)
//        });
//
//        auto whileLoop = Loop::create(std::move(condition), std::move(whileBody));
//
//        return whileLoop;
    }
};

#endif //CPP_EVA_TRANSFORMER_H
