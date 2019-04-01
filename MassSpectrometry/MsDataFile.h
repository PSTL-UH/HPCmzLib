#pragma once

#include "IMsDataFile.h"
#include "SourceFile.h"
#include "DeconvolutionFeatureWithMassesAndScans.h"
#include "MzSpectra/IsotopicEnvelope.h"
#include "MzSpectra/IMzSpectrum.h"
#include "MzSpectra/IMzPeak.h"

#include <vector>
#include <cmath>
#include <limits>
#include <functional>
#include <optional>
#include <type_traits>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (MsDataFile.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.

using namespace MzLibUtil;

namespace MassSpectrometry {
    /// <summary>
    /// A class for interacting with data collected from a Mass Spectrometer, and stored in a file
    /// </summary>
    template<typename TScan>
    class MsDataFile : public IMsDataFile<TScan> {
        static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, "TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");

    private:
        MassSpectrometry::SourceFile *privateSourceFile;

    protected:
        std::vector<TScan> Scans;

        MsDataFile(int numSpectra, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(sourceFile) {
            Scans = std::vector<TScan>(numSpectra);
        }

        MsDataFile(std::vector<TScan> &scans, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(sourceFile) {
            Scans = scans;
        }

    private:
        MsDataFile(MassSpectrometry::SourceFile *sourceFile) {
            this->SourceFile = sourceFile;
        }

    public:
        MassSpectrometry::SourceFile *getSourceFile() const override {
            return privateSourceFile;
        }

        int getNumSpectra() const override {
            return Scans.size();
        }

        virtual TScan GetOneBasedScan(int scanNumber) = 0;

        std::vector<TScan> GetMsScansInIndexRange(int FirstSpectrumNumber, int LastSpectrumNumber) {
            std::vector<TScan> v;
            for (int oneBasedSpectrumNumber = FirstSpectrumNumber; oneBasedSpectrumNumber <= LastSpectrumNumber; oneBasedSpectrumNumber++) {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent
                // to the C# 'yield' keyword:
                //yield return GetOneBasedScan(oneBasedSpectrumNumber);
                v.push_back(GetOneBasedScan(oneBasedSpectrumNumber));
            }
            return v;
        }

        std::vector<TScan> GetMsScansInTimeRange(double firstRT, double lastRT) override {
            int oneBasedSpectrumNumber = GetClosestOneBasedSpectrumNumber(firstRT);
            std::vector<TScan> v;
            while (oneBasedSpectrumNumber <= getNumSpectra()) {
                TScan scan = GetOneBasedScan(oneBasedSpectrumNumber);
                double rt = scan->getRetentionTime();
                if (rt < firstRT) {
                    oneBasedSpectrumNumber++;
                    continue;
                }
                if (rt > lastRT) {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an
                    // equivalent to the C# 'yield' keyword:
                    //yield break;
                    return v;
                }
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an
                // equivalent to the C# 'yield' keyword:
                //yield return scan;
                v.push_back (scan);
                oneBasedSpectrumNumber++;
            }
            return v;
        }

        int GetClosestOneBasedSpectrumNumber(double retentionTime) override {
            // TODO need to convert this to a binary search of some sort. Or if
            // the data is indexedMZML see if the indices work better.
            double bestDiff = std::numeric_limits<double>::max();
            for (int i = 0; i < getNumSpectra(); i++) {
                double diff = std::abs(GetOneBasedScan(i + 1)->getRetentionTime() - retentionTime);
                if (diff > bestDiff) {
                    return i;
                }
                bestDiff = diff;
            }
            return getNumSpectra();
        }

#ifdef LATER
        // don't know how to translate these, will have to see how it is used later.
        System::Collections::IEnumerator *IEnumerable_GetEnumerator() override {
            return GetMsScansInIndexRange(1, getNumSpectra()).begin();
        }

        IEnumerator<TScan> *GetEnumerator() {
            return GetMsScansInIndexRange(1, getNumSpectra()).begin();
        }
#endif

        std::vector<DeconvolutionFeatureWithMassesAndScans*> Deconvolute(std::optional<int> &minScan,
                                                                         std::optional<int> &maxScan,
                                                                         int maxAssumedChargeState,
                                                                         double deconvolutionTolerancePpm,
                                                                         double intensityRatioLimit,
                                                                         double aggregationTolerancePpm,
                                                                         std::function<bool(TScan)> scanFilterFunc) override {
            if ( !minScan.has_value()) {
                minScan = std::make_optional(1);
            }
            if ( !maxScan.has_value() ) {
                maxScan = std::make_optional( getNumSpectra());
            }

            auto allAggregateGroups = std::vector<std::vector<IsotopicEnvelope*>>(maxScan.value() - minScan.value() + 1);
#ifdef ORIG
            Parallel::ForEach(Partitioner::Create(minScan.value(), maxScan.value() + 1), [&] (std::any fff)
                );
#endif
            for ( int scanIndex = minScan.value(); scanIndex < maxScan.value()+1; scanIndex++)  {
                auto theScan = GetOneBasedScan(scanIndex);
                if (scanFilterFunc(theScan)) {
                    MzRange tempVar(0, std::numeric_limits<double>::infinity());
                    allAggregateGroups[scanIndex - minScan.value()] = theScan->getMassSpectrum()->Deconvolute(&tempVar,
                                          maxAssumedChargeState, deconvolutionTolerancePpm, intensityRatioLimit); //.toList()
                }               
            }

            std::vector<DeconvolutionFeatureWithMassesAndScans*> currentListOfGroups = std::vector<DeconvolutionFeatureWithMassesAndScans*>();
            for (int scanIndex = minScan.value(); scanIndex <= maxScan.value(); scanIndex++) {
                if (allAggregateGroups[scanIndex - minScan.value()].empty()) {
                    continue;
                }
                for (auto isotopicEnvelope : allAggregateGroups[scanIndex - minScan.value()]) {
                    DeconvolutionFeatureWithMassesAndScans *matchingGroup = nullptr;
                    auto mass = isotopicEnvelope->monoisotopicMass;
                    for (auto possibleGroup : currentListOfGroups) {
                        auto possibleGroupMass = possibleGroup->getMass();
                        if (std::abs(mass - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm || std::abs(mass + 1.002868314 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm || std::abs(mass + 2.005408917 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm || std::abs(mass + 3.007841294 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm || std::abs(mass - 1.002868314 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm || std::abs(mass - 2.005408917 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm || std::abs(mass - 3.007841294 - possibleGroupMass) / possibleGroupMass * 1e6 <= aggregationTolerancePpm) {
                            matchingGroup = possibleGroup;
                            matchingGroup->AddEnvelope(isotopicEnvelope, scanIndex, GetOneBasedScan(scanIndex)->getRetentionTime());
                            break;
                        }
                    }

                    if (matchingGroup == nullptr) {
                        auto newGroupScans = new DeconvolutionFeatureWithMassesAndScans();
                        newGroupScans->AddEnvelope(isotopicEnvelope, scanIndex, GetOneBasedScan(scanIndex)->getRetentionTime());
                        currentListOfGroups.push_back(newGroupScans);

                        //C# TO C++ CONVERTER TODO TASK: A 'delete newGroupScans' statement was not added since
                        // newGroupScans was passed to a method or constructor. Handle memory management manually.
                    }
                }
                std::vector<DeconvolutionFeatureWithMassesAndScans*> v;
#ifdef ORIG
                for (auto ok : currentListOfGroups.Where([&] (std::any b) {
                    return b::MaxScanIndex < scanIndex;
                        }));
#endif
                std::vector<MassSpectrometry::DeconvolutionFeatureWithMassesAndScans*>::const_iterator ok;
                for ( ok = currentListOfGroups.begin(); ok != currentListOfGroups.end(); ++ok )  {
                    auto okk = *ok;
                    if (okk->getMaxScanIndex() < scanIndex ) {
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        //yield return ok;
                        v.push_back (okk);
                        currentListOfGroups.erase (ok);
                    }                        
#ifdef ORIG
//                    currentListOfGroups.RemoveAll([&] (std::any b) {
//                            return b::MaxScanIndex < scanIndex;
//                        });
#endif
                }

                for (auto ok : currentListOfGroups) {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    //yield return ok;
                    v.push_back (ok);
                }
                return v;
            }
        }

        class ReverseComparer {
        public:
            int Compare(double x, double y);
        };
    };
}
