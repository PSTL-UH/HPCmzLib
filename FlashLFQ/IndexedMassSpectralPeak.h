#pragma once

#include <string>
#include <any>


namespace FlashLFQ
{
    class IndexedMassSpectralPeak
    {
    public:
        const int ZeroBasedMs1ScanIndex;
        const double Mz;
        const double RetentionTime;
        const double Intensity;

        IndexedMassSpectralPeak(double mz, double intensity, int zeroBasedMs1ScanIndex, double retentionTime);

        bool Equals(IndexedMassSpectralPeak* obj);

        int GetHashCode();

        std::string ToString();

        template <class Archive>
        void save( Archive & ar ) const
        {
            ar( cereal::make_nvp("Mz", Mz) );
            ar( cereal::make_nvp("Intensity", Intensity) );
            ar( cereal::make_nvp("ZeroBasedMs1ScanIndex", ZeroBasedMs1ScanIndex) );
            ar( cereal::make_nvp("RetentionTime", RetentionTime) );
        }

        template <class Archive>
        static void load_and_construct( Archive & ar, cereal::construct<IndexedMassSpectralPeak> & construct )
        {
            int ZeroBasedMs1ScanIndex;
            double Mz, RetentionTime, Intensity;

            ar( cereal::make_nvp("Mz", Mz) );
            ar( cereal::make_nvp("Intensity", Intensity) );
            ar( cereal::make_nvp("ZeroBasedMs1ScanIndex", ZeroBasedMs1ScanIndex) );
            ar( cereal::make_nvp("RetentionTime", RetentionTime) );

            construct( Mz, Intensity, ZeroBasedMs1ScanIndex, RetentionTime ); // calls MyType( x )
        }
    };
}
