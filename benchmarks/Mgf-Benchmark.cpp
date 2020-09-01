#include <vector>
#include <string>
#include "../Mgf/Mgf.h"
using namespace IO::Mgf;

#include "../UsefulProteomicsDatabases/Loaders.h"

#include <chrono>

int main( int argc, char *argv[] )
{

    std::cout << "Loading Periodic Table\n" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
    //read mgf file
    std::cout << "Reading Mgf file " << argv[1] << std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    auto msData = Mgf::LoadAllStaticData(argv[1]);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to read mgf:  " << std::chrono::duration_cast<std::chrono::milliseconds>( t6 - t5 ).count() << "\n" << std::endl;


    return 0;
}


