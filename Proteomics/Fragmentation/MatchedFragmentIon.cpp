#include "MatchedFragmentIon.h"
#include "Product.h"
#include "../../Chemistry/ClassExtensions.h"
#include "stringhelper.h"

using namespace Chemistry;
namespace Proteomics
{
    namespace Fragmentation
    {

        MatchedFragmentIon::MatchedFragmentIon(Product *neutralTheoreticalProduct, double experMz,
                                               double experIntensity, int charge) :
            NeutralTheoreticalProduct(neutralTheoreticalProduct), Mz(experMz), Intensity(experIntensity), Charge(charge)
        {
        }

        double MatchedFragmentIon::getMassErrorDa() const
        {
            return Chemistry::ClassExtensions::ToMass(Mz, Charge) - NeutralTheoreticalProduct->NeutralMass;
        }

        double MatchedFragmentIon::getMassErrorPpm() const
        {
            return (getMassErrorDa() / NeutralTheoreticalProduct->NeutralMass) * 1e6;
        }

        std::string MatchedFragmentIon::getAnnotation() const
        {
            StringBuilder *sb = new StringBuilder();

            bool containsNeutralLoss = NeutralTheoreticalProduct->NeutralLoss != 0;

            if (containsNeutralLoss)
            {
                sb->append("(");
            }

            sb->append(NeutralTheoreticalProduct->getAnnotation());

            if (containsNeutralLoss)
            {
                sb->append(")");
            }

            sb->append("+");
            sb->append(Charge);

            std::string s = sb->toString(); 
            delete sb;
            return s;
        }

        std::string MatchedFragmentIon::ToString()
        {
            // we add the blank space in the tostring because the values are treated like
            // integers and looked up as index in the enum instead of being converted to just string and concatenated
            ProductType pT = NeutralTheoreticalProduct->productType;

            std::ostringstream out;
            out << NeutralTheoreticalProduct->TerminusFragment->FragmentNumber << "+" ;
            out << Charge << "\t;" << NeutralTheoreticalProduct->NeutralMass;
            return ProductTypeToString(pT) + out.str();
        }

        bool MatchedFragmentIon::Equals( MatchedFragmentIon *other)
        {
            
            return this->NeutralTheoreticalProduct->Equals(other->NeutralTheoreticalProduct) &&
                this->Charge    == other->Charge     &&
                this->Mz        == other->Mz         &&
                this->Intensity == other->Intensity;
        }

        int MatchedFragmentIon::GetHashCode()
        {
            return StringHelper::GetHashCode(std::to_string(Mz));
        }

        int MatchedFragmentIon::Pack(char *buf, size_t *buf_len, MatchedFragmentIon *MaF)
        {
            std::stringstream output;

            output << MaF->Mz << "\t" << MaF->Intensity <<  "\t" << MaF->Charge << "\t";

            auto product = MaF->NeutralTheoreticalProduct;
            auto pType = product->productType;
            output << product->NeutralLoss << "\t" <<
                Fragmentation::ProductTypeToString(pType) << "\t";

            auto tfragment = product->TerminusFragment;
            output <<  Fragmentation::FragmentationTerminusToString(tfragment->Terminus) << "\t" <<
                tfragment->NeutralMass << "\t" << tfragment->FragmentNumber << "\t" <<
                tfragment->AminoAcidPosition << std::endl;
                            
            std::string sstring = output.str();
            size_t slen = sstring.length();
            if ( slen > *buf_len )  {
                *buf_len = slen;
                return -1;
            }
            else {
                *buf_len = slen;
                memcpy (buf, sstring.c_str(), slen );
            }
            return (int)slen;            
        }

        void MatchedFragmentIon::Unpack(char *buf, size_t buf_len, MatchedFragmentIon **newMaF)
        {
            std::string input (buf);

            std::vector<std::string> splits = StringHelper::split(input, '\t');
            double mz, intensity;
            int charge;
            mz        = std::stod(splits[0]);
            intensity = std::stod(splits[1]);
            charge    = std::stoi (splits[2]);

            double neutralLoss;
            neutralLoss = std::stod(splits[3]);
            auto pType = Fragmentation::ProductTypeFromString (splits[4]);

            double nMass;
            int fNumber, AAPos;
            auto fTerminus = Fragmentation::FragmentationTerminusFromString(splits[5]);
            nMass = std::stod(splits[6]);
            fNumber = std::stoi(splits[7]);
            AAPos = std::stoi (splits[8]);

            auto terminusFragment = new NeutralTerminusFragment (fTerminus, nMass, fNumber, AAPos);
            auto product = new Product (pType, terminusFragment, neutralLoss );
            
            MatchedFragmentIon *newM = new MatchedFragmentIon (product, mz, intensity, charge);
            *newMaF = newM;
        }

    }
}
