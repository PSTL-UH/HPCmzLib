#include "MatchedFragmentIon.h"
#include "Product.h"
#include "../../Chemistry/ClassExtensions.h"
//#include "stringhelper.h"
#include "BinaryPack.h"
#include <iomanip>

using namespace Chemistry;
namespace Proteomics
{
    namespace Fragmentation
    {

        MatchedFragmentIon::MatchedFragmentIon(Product *neutralTheoreticalProduct, double experMz,
                                               double experIntensity, int charge) :
            Mz(experMz), Intensity(experIntensity), Charge(charge)
        {
            NeutralTheoreticalProduct = new Product (neutralTheoreticalProduct->productType, neutralTheoreticalProduct->TerminusFragment, neutralTheoreticalProduct->NeutralLoss);
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

        int MatchedFragmentIon::Pack(char *buf, size_t &buf_len,
                                     const std::vector<MatchedFragmentIon *> &MaFVec)
        {
            size_t pos = 0;
            int ret;
            
            for ( auto MaF: MaFVec ) {
                size_t len = buf_len - pos;
                ret = MatchedFragmentIon::Pack(buf+pos, len, MaF);
                if ( ret == -1 ) {
                    buf_len = pos + len;
                    return ret;
                }
                pos += len;
            }
            buf_len = pos;
            return pos;
        }
        
        int MatchedFragmentIon::Pack(char *buf, size_t &buf_len, MatchedFragmentIon *MaF)
        {
            int tmplen = 256;
            char tmpbuf[256];
            size_t retlen;

            // Initial position is sizeof(int), since we will copy the overall length at the beginning.
            size_t pos=sizeof(int);
            
            retlen = BinaryPack::PackDouble(tmpbuf+pos, MaF->Mz);
            pos += retlen;
            retlen = BinaryPack::PackDouble(tmpbuf+pos, MaF->Intensity);
            pos += retlen;
            retlen = BinaryPack::PackInt(tmpbuf+pos, MaF->Charge);
            pos += retlen;
            
            auto product = MaF->NeutralTheoreticalProduct;
            auto pType = product->productType;
            retlen = BinaryPack::PackDouble(tmpbuf+pos, product->NeutralLoss);
            pos += retlen;
            retlen = BinaryPack::PackString(tmpbuf+pos, Fragmentation::ProductTypeToString(pType));
            pos += retlen;

            auto tfragment = product->TerminusFragment;
            retlen = BinaryPack::PackString(tmpbuf+pos, Fragmentation::FragmentationTerminusToString(tfragment->Terminus));
            pos += retlen;
            retlen = BinaryPack::PackDouble(tmpbuf+pos, tfragment->NeutralMass);
            pos += retlen;
            retlen = BinaryPack::PackInt(tmpbuf+pos, tfragment->FragmentNumber);
            pos += retlen;
            retlen = BinaryPack::PackInt(tmpbuf+pos, tfragment->AminoAcidPosition);
            pos += retlen;

            // Last step: save the total size of the line at the beginning. We reserved the memory for that.
            retlen = BinaryPack::PackInt(tmpbuf, (int)pos);
            
            if ( pos > buf_len )  {
                buf_len = pos;
                return -1;
            }
            else {
                buf_len = pos;
                memcpy (buf, tmpbuf, pos );
            }
            return (int)pos;            
        }


        void MatchedFragmentIon::Unpack(char *buf, size_t buf_len, size_t &len,
                                        std::vector<MatchedFragmentIon *> &newMaFVec,
                                        int count )
        {
            //std::string input_buf (buf);
            //std::vector<std::string> lines = StringHelper::split(input_buf, '\n');
            std::vector<char *>lines = BinaryPack::SplitLines(buf, buf_len);
            
            size_t total_len=0;
            int counter=0;
            for ( auto line : lines ) {
                size_t tmp;
                MatchedFragmentIon *newMaF;
                MatchedFragmentIon::Unpack(line, tmp, &newMaF);
                total_len += tmp;
                newMaFVec.push_back(newMaF);
                counter ++;
                if ( counter == count ) break;
            }
            len = total_len;
        }
        
        void MatchedFragmentIon::Unpack(char *buf, size_t buf_len, size_t &len, MatchedFragmentIon **newMaF)
        {
            MatchedFragmentIon::Unpack(buf, len, newMaF);
        }
        
        void MatchedFragmentIon::Unpack(char* input, size_t &len, MatchedFragmentIon **newMaF)
        {
            size_t retlen, pos=0;

            int total_len;
            retlen = BinaryPack::UnpackInt(input, total_len);
            pos += retlen;
            
            double mz, intensity;
            retlen = BinaryPack::UnpackDouble(input+pos, mz);
            pos += retlen;
            retlen = BinaryPack::UnpackDouble(input+pos, intensity);
            pos += retlen;
            
            int charge;
            retlen = BinaryPack::UnpackInt(input+pos, charge);
            pos += retlen;

            double neutralLoss;
            retlen = BinaryPack::UnpackDouble(input+pos, neutralLoss);
            pos += retlen;

            std::string pTypeString;
            retlen = BinaryPack::UnpackString(input+pos, pTypeString);
            pos += retlen;           
            auto pType = Fragmentation::ProductTypeFromString (pTypeString);

            std::string fTerminusString;
            retlen = BinaryPack::UnpackString(input+pos, fTerminusString);
            pos += retlen;           
            auto fTerminus = Fragmentation::FragmentationTerminusFromString(fTerminusString);

            double nMass;
            retlen = BinaryPack::UnpackDouble(input+pos, nMass);
            pos += retlen;

            int fNumber, AAPos;
            retlen = BinaryPack::UnpackInt(input+pos, fNumber);
            pos += retlen;
            retlen = BinaryPack::UnpackInt(input+pos, AAPos);
            pos += retlen;

            auto terminusFragment = new NeutralTerminusFragment (fTerminus, nMass, fNumber, AAPos);
            auto product = new Product (pType, terminusFragment, neutralLoss );
            
            MatchedFragmentIon *newM = new MatchedFragmentIon (product, mz, intensity, charge);

            *newMaF = newM;
            len = pos;
        }
    }
}
