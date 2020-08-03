#include "duckdb/function/table/sqlite_functions.hpp"

namespace duckdb {

struct PragmaVersionData : public TableFunctionData {
	PragmaVersionData() : done(false) {
	}
	bool done;
};

static unique_ptr<FunctionData> pragma_version_bind(ClientContext &context, vector<Value> inputs,
                                                    vector<SQLType> &return_types, vector<string> &names) {
	names.push_back("library_version");
	return_types.push_back(SQLType::VARCHAR);
    names.push_back("source_id");
    return_types.push_back(SQLType::VARCHAR);

	return make_unique<PragmaVersionData>();
}

static void pragma_version_info(ClientContext &context, vector<Value> &input, DataChunk &output,
                                FunctionData *dataptr) {
	auto &data = *((PragmaVersionData *)dataptr);
	assert(input.size() == 0);
	if (data.done) {
		// finished returning values
		return;
	}
	output.SetCardinality(1);
	output.SetValue(0, 0, "DuckDB");
	output.SetValue(1, 0, DUCKDB_SOURCE_ID);
	data.done = true;
}

void PragmaVersion::RegisterFunction(BuiltinFunctions &set) {
	set.AddFunction(TableFunction("pragma_version", {}, pragma_version_bind, pragma_version_info, nullptr));
}

} // namespace duckdb
