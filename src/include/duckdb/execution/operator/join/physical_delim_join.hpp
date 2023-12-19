//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/join/physical_delim_join.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/types/chunk_collection.hpp"
#include "duckdb/execution/physical_operator.hpp"

namespace duckdb {

class PhysicalHashAggregate;

//! PhysicalRightDelimJoin represents a join where the RHS will be duplicate eliminated and pushed into a
//! PhysicalColumnDataScan in the LHS.
class PhysicalDelimJoin : public PhysicalOperator {
public:
	PhysicalDelimJoin(PhysicalOperatorType type, vector<LogicalType> types, unique_ptr<PhysicalOperator> original_join,
	                  vector<const_reference<PhysicalOperator>> delim_scans, idx_t estimated_cardinality);

	unique_ptr<PhysicalOperator> join;
	unique_ptr<PhysicalHashAggregate> distinct;
	vector<const_reference<PhysicalOperator>> delim_scans;

public:
	vector<const_reference<PhysicalOperator>> GetChildren() const override;

	bool IsSink() const override {
		return true;
	}
	bool ParallelSink() const override {
		return true;
	}
	OrderPreservationType SourceOrder() const override {
		return OrderPreservationType::NO_ORDER;
	}
	bool SinkOrderDependent() const override {
		return false;
	}

	string ParamsToString() const override;
};

} // namespace duckdb
