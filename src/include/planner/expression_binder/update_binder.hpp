//===----------------------------------------------------------------------===//
//                         DuckDB
//
// planner/expression_binder/update_binder.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "planner/expression_binder.hpp"

namespace duckdb {

//! The UPDATE binder is responsible for binding an expression within an UPDATE statement
class UpdateBinder : public ExpressionBinder {
public:
	UpdateBinder(Binder &binder, ClientContext &context);

protected:
	BindResult BindExpression(ParsedExpression &expr, count_t depth, bool root_expression = false) override;
};

} // namespace duckdb
