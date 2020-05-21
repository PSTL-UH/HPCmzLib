BENCHMARKS PROGRAM.CS

First, rename file to Program.cs

To compile Program.cs use the following command:
dotnet publish -f netcoreapp2.0 -c Release -r rhel.7-x64 --self-contained yes

Compiling with create the necessary files and directories.  The executable is stored in:
bin/Release/netcoreapp2.0/rhel.7-x64/publish

change directories to bin/Release/netcoreapp2.0/rhel.7-x64/publish and execute CMD executable with the following command:

./CMD toml-filename number-of-toml-values mzml-filename-to-read mzml-filename-to-write

For example:

./CMD /home/nrbiddle/MetaMorpheus-0.0.295/CMD/test_toml_2.toml 20000 /home/nrbiddle/MetaMorpheus-0.0.295/CMD/sliced-raw.mzML /home/nrbiddle/MetaMorpheus-0.0.295/CMD/test_write_mzml2.mzML
