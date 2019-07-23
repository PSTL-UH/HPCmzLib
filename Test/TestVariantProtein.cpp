#include "TestVariantProtein.h"
#include "../Proteomics/Protein/Protein.h"
#include "../UsefulProteomicsDatabases/DecoyType.h"
#include "../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../UsefulProteomicsDatabases/ProteinDbWriter.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test
{

    void VariantProteinTests::MakeVariantFasta()
    {
        std::unordered_map<string, Modification> un;
        std::vector<Protein*> proteins = ProteinDbLoader::LoadProteinXML(R"(E:\ProjectsActive\JurkatProteogenomics\180413\combined_1-trimmed-pair1Aligned.sortedByCoord.outProcessed.out.fixedQuals.split.concat.sorted.snpEffAnnotated.protein.xml)", true, DecoyType::None, std::vector<Modification>(), false, std::vector<std::string>(), un);
        std::vector<ProteinWithAppliedVariants*> variantProteins = proteins.SelectMany([&] (std::any p)
        {
            p::GetVariantProteins();
        }).ToList();
        std::vector<ProteinWithAppliedVariants*> variantProteins2 = variantProteins.Select([&] (std::any p)
        {
            Protein tempVar(p::Protein::BaseSequence, p::Protein::Accession, p::Protein::Organism, p::Protein::GeneNames::ToList(), p::Protein::OneBasedPossibleLocalizedModifications, p::Protein::ProteolysisProducts::ToList(), p::Protein->Name + std::string::Join(",", p::AppliedSequenceVariations->Select([&] (std::any d)
            {
                d::Description;
            })), p::Protein->FullName + std::string::Join(",", p::AppliedSequenceVariations->Select([&] (std::any d)
            {
                d::Description;
            })), p::IsDecoy, p::IsContaminant, p::DatabaseReferences::ToList(), p::SequenceVariations::ToList(), p::DisulfideBonds::ToList(), p::DatabaseFilePath);
            new ProteinWithAppliedVariants(p::BaseSequence, &tempVar, p::AppliedSequenceVariations, p::Individual);
        }).ToList();
        ProteinDbWriter::WriteFastaDatabase(variantProteins2.OfType<Protein*>().ToList(), R"(E:\ProjectsActive\Spritz\mmTesting\variantproteins.fasta)", "|");
    }
}
