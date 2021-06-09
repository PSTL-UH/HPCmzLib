#include <vector>
#include <string>
#include "../MzML/Mzml.h"
#include "../MzML/MzmlMethods.h"
using namespace IO::MzML;

#include "../UsefulProteomicsDatabases/Loaders.h"

#include "../include/TomlReadWrite.h"

#include <chrono>

//argv arguments:  toml file name, number of toml entries, mzml filename to read, mzml filename to write

int main( int argc, char *argv[] )
{

    std::cout << "Welcome to MetaMorpheus" << std::endl;

    std::cout << "Loading Periodic Table\n" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    

    //generate toml key-value pairs
    toml::Value v;
    long num = strtol(argv[2], NULL, 10);
    std::cout << "generating toml data with " << std::to_string(num) << " key-value pairs\n" << std::endl;
    for (long i = 0; i < num; i++){
        std::string key = "key" + std::to_string(i);
        v.set(key, i);
    }

    //write toml data to file
    std::cout << "Writing toml data to file " << argv[1] << std::endl;
    Toml trw;
    auto t1 = std::chrono::high_resolution_clock::now();
    trw.tomlWriteNewFile(argv[1], v);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to write toml:  " << std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count() << "\n"<< std::endl;

    // read toml file
    std::cout << "Reading file " << argv[1] << std::endl;
    // Toml trw;
    auto t3 = std::chrono::high_resolution_clock::now();
    toml::Value r = trw.tomlReadFile(argv[1]);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to read toml:  " << std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count() << "\n" << std::endl;

    
    //read mzml file
    std::cout << "Reading file " << argv[3] << std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    auto msData = Mzml::LoadAllStaticData(argv[3]);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to read mzml:  " << std::chrono::duration_cast<std::chrono::microseconds>( t6 - t5 ).count() << "\n" << std::endl;


    //write mzml file
#ifdef LATER
    std::cout << "Writing file " << argv[4] << std::endl;
    auto t7 = std::chrono::high_resolution_clock::now();
    MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(msData, argv[4], false);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to write mzml:  " << std::chrono::duration_cast<std::chrono::microseconds>( t8 - t7 ).count() << std::endl;

#endif
    return 0;
}


