#include "duckdb_python/pybind11/pybind_wrapper.hpp"
#include "duckdb_python/expression/pyexpression.hpp"
#include "duckdb/common/helper.hpp"
#include "duckdb/common/vector.hpp"

namespace duckdb {

void InitializeStaticMethods(py::module_ &m) {
	const char *docs;

	// Constant Expression
	docs = "Create a constant expression from the provided value";
	m.def("ConstantExpression", &DuckDBPyExpression::ConstantExpression, py::arg("value"), docs);

	// ColumnRef Expression
	docs = "Create a column reference from the provided column name";
	m.def("ColumnExpression", &DuckDBPyExpression::ColumnExpression, py::arg("name"), docs);

	// Function Expression
	docs = "";
	m.def("BinaryFunctionExpression", &DuckDBPyExpression::BinaryFunctionExpression, py::arg("function_name"),
	      py::arg("arg_one"), py::arg("arg_two"), docs);
}

void DuckDBPyExpression::Initialize(py::module_ &m) {
	auto expression =
	    py::class_<DuckDBPyExpression, shared_ptr<DuckDBPyExpression>>(m, "Expression", py::module_local());

	InitializeStaticMethods(m);

	const char *docs;

	docs = R"(
    Print the stringified version of the expression.
	)";
	expression.def("show", &DuckDBPyExpression::Print, docs);

	docs = R"(
        Return the stringified version of the expression.

        Returns:
            str: The string representation.
    )";
	expression.def("__repr__", &DuckDBPyExpression::ToString, docs);

	docs = R"(
		Add two expressions.

		Parameters:
			expr: The expression to do add together with

		Returns:
			FunctionExpression: A '+' on the two input expressions.
	)";
	expression.def("__add__", &DuckDBPyExpression::Add, py::arg("expr"), docs);
}

} // namespace duckdb
