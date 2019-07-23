#include "TestProductMassesMightHaveDuplicates.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../MassSpectrometry/Enums/DissociationType.h"

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestProductMassesMightHaveDuplicates::privateStopwatch;

    Stopwatch *TestProductMassesMightHaveDuplicates::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestProductMassesMightHaveDuplicates::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestProductMassesMightHaveDuplicates::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestProductMassesMightHaveDuplicates::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestProductMassesMightHaveDuplicates::Test_UnmodifiedPeptide_AllProductType_fragmentMasses()
    {
        Protein *p = new Protein("PET", "accession");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).front();

        auto allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::Unknown, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> { }));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::CID, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {227, 120, 249}));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::IRMPD, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {98, 227, 120, 249}));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::ECD, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {115, 244, 120, 249, 104, 233}));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::PQD, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> { }));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::ETD, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {115, 244, 120, 249, 104, 233}));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {98, 227, 120, 249}));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::AnyActivationType, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {98, 227, 120, 249}));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::EThcD, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> {98, 227, 115, 244, 120, 249, 104, 233}));

        DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom] = { };
        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::Custom, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> { }));

        allFragmentIonMzs = std::unordered_set<int>(aPeptideWithSetModifications->Fragment(DissociationType::ISCID, FragmentationTerminus::Both)->Select([&] (std::any i)
        {
            static_cast<int>(BankersRounding::round(i::NeutralMass::ToMz(1)));
        }));
        Assert::IsTrue(allFragmentIonMzs.SetEquals(std::unordered_set<int> { }));

//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete p;
    }
}
