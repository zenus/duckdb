import os
import re
from python_helpers import open_utf8


def execute_system_command(cmd):
    print(cmd)
    retcode = os.system(cmd)
    print(retcode)
    if retcode != 0:
        raise Exception


def replace_in_file(fname, regex, replace):
    with open_utf8(fname, 'r') as f:
        contents = f.read()
    contents = re.sub(regex, replace, contents)
    with open_utf8(fname, 'w+') as f:
        f.write(contents)


current_dir = os.getcwd()
build_dir = os.path.join(os.getcwd(), 'build', 'release')

block_size = 16384
vector_size = 2048
print("TESTING BLOCK_ALLOC_SIZE=%d" % (block_size,))
print("TESTING STANDARD_VECTOR_SIZE=%d" % (vector_size,))

replace_in_file(
    'src/include/duckdb/storage/storage_info.hpp',
    r'constexpr static idx_t BLOCK_ALLOC_SIZE = \d+',
    'constexpr static idx_t BLOCK_ALLOC_SIZE = %d' % (block_size,),
)

replace_in_file(
    'src/include/duckdb/common/vector_size.hpp',
    r'#define STANDARD_VECTOR_SIZE \d+',
    '#define STANDARD_VECTOR_SIZE %d' % (vector_size,),
)

execute_system_command('rm -rf build')
execute_system_command('make relassert')
execute_system_command('python3 scripts/run_tests_one_by_one.py build/relassert/test/unittest "*"')

vector_size = 512
print("TESTING BLOCK_ALLOC_SIZE=%d" % (block_size,))
print("TESTING STANDARD_VECTOR_SIZE=%d" % (vector_size,))

replace_in_file(
    'src/include/duckdb/common/vector_size.hpp',
    r'#define STANDARD_VECTOR_SIZE \d+',
    '#define STANDARD_VECTOR_SIZE %d' % (vector_size,),
)

execute_system_command('rm -rf build')
execute_system_command('make relassert')
execute_system_command('build/relassert/test/unittest')
