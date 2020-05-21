
First, ensure that elements.dat is linked in the benchmarks directory
Compile Benchmarks.cpp with the MAKEFILE

execute with the following command:

./Benchmark toml_file_name number_key_value_pairs mzml_filename_to_read mzml_filename_to_write


example:

./Benchmark test.toml 10000 sliced-raw.mzML test_write.mzML

