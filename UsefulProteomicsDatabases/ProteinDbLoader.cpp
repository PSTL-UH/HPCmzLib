﻿#include "ProteinDbLoader.h"
#include "../Proteomics/Modification.h"
#include "../Proteomics/Protein.h"
#include "../Proteomics/ProteolysisProduct.h"
#include "../Proteomics/SequenceVariation.h"
#include "../Proteomics/DisulfideBond.h"
#include "../Proteomics/DatabaseReference.h"
#include "PtmListLoader.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases {

Regex *ProteinDbLoader::uniprot_accession_expression = new Regex(LR"(([A-Z0-9_]+))");
Regex *ProteinDbLoader::uniprot_fullName_expression = new Regex(LR"(\|([^\|]+)\sOS=)");
Regex *ProteinDbLoader::uniprot_gene_expression = new Regex(LR"(GN=([^ ]+))");
Regex *ProteinDbLoader::ensembl_accession_expression = new Regex(LR"(([A-Z0-9_]+))");
Regex *ProteinDbLoader::ensembl_fullName_expression = new Regex(LR"((pep:.*))");
Regex *ProteinDbLoader::ensembl_gene_expression = new Regex(LR"(gene:([^ ]+))");
std::wstring ProteinDbLoader::last_database_location;
std::vector<Modification*> ProteinDbLoader::protein_xml_modlist;

    std::vector<Protein*> ProteinDbLoader::LoadProteinXML(const std::wstring &proteinDbLocation, bool generateTargetProteins, DecoyType decoyType, std::vector<Modification*> &allKnownModifications, bool IsContaminant, std::vector<std::wstring> &modTypesToExclude, std::unordered_map<std::wstring, Modification*> &unknownModifications) {
        std::vector<Modification*> prespecified = GetPtmListFromProteinXml(proteinDbLocation);

        std::unordered_map<std::wstring, std::vector<Modification*>> mod_dict;
        if (prespecified.size() > 0 || allKnownModifications.size()() > 0) {
            mod_dict = GetModificationDict(std::unordered_set<Modification*>(prespecified.Concat(allKnownModifications)));
        }

        std::vector<Protein*> result;
        unknownModifications = std::unordered_map<std::wstring, Modification*>();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new FileStream(proteinDbLocation, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
            auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
            Regex *substituteWhitespace = new Regex(LR"(\s+)");

            GZipStream tempVar(stream, CompressionMode::Decompress);
            Stream *uniprotXmlFileStream = StringHelper::endsWith(proteinDbLocation, L".gz") ? static_cast<Stream*>(&tempVar): stream;

            std::vector<std::wstring> nodes(6);

            std::wstring accession = L"";
            std::wstring name = L"";
            std::wstring full_name = L"";
            std::wstring sequence = L"";
            std::wstring feature_type = L"";
            std::wstring feature_description = L"";
            std::wstring original_value = L""; // if no content is found, assume it is empty, not null (e.g. <original>A</original><variation/> for a deletion event)
            std::wstring variation_value = L"";
            std::wstring dbReference_type = L"";
            std::wstring dbReference_id = L"";
            std::vector<std::wstring> property_types;
            std::vector<std::wstring> property_values;
            int oneBasedfeature_position = -1;
            std::optional<int> oneBasedbeginPosition = std::nullopt;
            std::optional<int> oneBasedendPosition = std::nullopt;
            std::vector<ProteolysisProduct*> proteolysisProducts;
            std::vector<SequenceVariation*> sequenceVariations;
            std::vector<DisulfideBond*> disulfideBonds;
            auto oneBasedModifications = std::unordered_map<int, std::vector<Modification*>>();
            std::vector<std::tuple<std::wstring, std::wstring>> gene_names;
            bool reading_gene = false;
            std::vector<DatabaseReference*> databaseReferences;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (XmlReader xml = XmlReader.Create(uniprotXmlFileStream))
            {
                XmlReader xml = XmlReader::Create(uniprotXmlFileStream);
                while (xml.Read()) {
                    switch (xml.NodeType) {
                        case XmlNodeType::Element: {
                            nodes[xml.Depth] = xml.Name;
                            int outValue;
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                            switch (xml.Name)
//ORIGINAL LINE: case "accession":
                            if (xml.Name == L"accession") {
                                    if (accession == L"") {
                                        accession = xml.ReadElementString();
                                    }

                            }
//ORIGINAL LINE: case "name":
                            else if (xml.Name == L"name") {
                                    if (xml.Depth == 2) {
                                        name = xml.ReadElementString();
                                    }
                                    if (reading_gene) {
                                        gene_names.push_back(std::tuple<std::wstring, std::wstring>(xml.GetAttribute(L"type"), xml.ReadElementString()));
                                    }

                            }
//ORIGINAL LINE: case "gene":
                            else if (xml.Name == L"gene") {
                                    reading_gene = true;

                            }
//ORIGINAL LINE: case "fullName":
                            else if (xml.Name == L"fullName") {
                                    if (full_name == L"") {
                                        full_name = xml.ReadElementString();
                                    }

                            }
//ORIGINAL LINE: case "feature":
                            else if (xml.Name == L"feature") {
                                    feature_type = xml.GetAttribute(L"type");
                                    feature_description = xml.GetAttribute(L"description");

                            }
//ORIGINAL LINE: case "original":
                            else if (xml.Name == L"original") {
                                    original_value = xml.ReadElementString();

                            }
//ORIGINAL LINE: case "variation":
                            else if (xml.Name == L"variation") {
                                    variation_value = xml.ReadElementString();

                            }
//ORIGINAL LINE: case "dbReference":
                            else if (xml.Name == L"dbReference") {
                                    property_types.clear();
                                    property_values.clear();
                                    dbReference_type = xml.GetAttribute(L"type");
                                    dbReference_id = xml.GetAttribute(L"id");

                            }
//ORIGINAL LINE: case "property":
                            else if (xml.Name == L"property") {
                                    property_types.push_back(xml.GetAttribute(L"type"));
                                    property_values.push_back(xml.GetAttribute(L"value"));

                            }
//ORIGINAL LINE: case "position":
                            else if (xml.Name == L"position") {
                                    oneBasedfeature_position = std::stoi(xml.GetAttribute(L"position"));

                            }
//ORIGINAL LINE: case "begin":
                            else if (xml.Name == L"begin") {
                                    oneBasedbeginPosition = int::TryParse(xml.GetAttribute(L"position"), outValue) ? static_cast<std::optional<int>>(outValue): nullptr;

                            }
//ORIGINAL LINE: case "end":
                            else if (xml.Name == L"end") {
                                    oneBasedendPosition = int::TryParse(xml.GetAttribute(L"position"), outValue) ? static_cast<std::optional<int>>(outValue): nullptr;

                            }
//ORIGINAL LINE: case "sequence":
                            else if (xml.Name == L"sequence") {
                                    sequence = substituteWhitespace->Replace(xml.ReadElementString(), L"");
                            }
                            break;

                        }
                        case XmlNodeType::EndElement:
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                            switch (xml.Name)
//ORIGINAL LINE: case "feature":
                            if (xml.Name == L"feature") {
                                    if (feature_type == L"modified residue") {
                                        feature_description = StringHelper::split(feature_description, L';')[0];

                                        // Create new entry for this residue, if needed
                                        List<Modification*> residue_modifications;
                                        std::unordered_map<int, std::vector<Modification*>>::const_iterator oneBasedModifications_iterator = oneBasedModifications.find(oneBasedfeature_position);
                                        if (oneBasedModifications_iterator == oneBasedModifications.end()) {
                                            residue_modifications = oneBasedModifications_iterator->second;
                                            residue_modifications = std::vector<Modification*>();
                                            oneBasedModifications.emplace(oneBasedfeature_position, residue_modifications);
                                        }
                                        else {
                                            residue_modifications = oneBasedModifications_iterator->second;
                                        }
                                        if (mod_dict.find(feature_description) != mod_dict.end()) {
                                            // Known and not of a type in the exclusion list
                                            std::vector<Modification*> mods = mod_dict[feature_description].Where([&] (std::any m) {
                                                !std::find(modTypesToExclude.begin(), modTypesToExclude.end(), m::modificationType) != modTypesToExclude.end();
                                            }).ToList();
                                            if (mods.empty() && oneBasedModifications[oneBasedfeature_position].empty()) {
                                                oneBasedModifications.erase(oneBasedfeature_position);
                                            }
                                            else {
                                                oneBasedModifications[oneBasedfeature_position].insert(oneBasedModifications[oneBasedfeature_position].end(), mods.begin(), mods.end());
                                            }
                                        }
                                        else if (unknownModifications.find(feature_description) != unknownModifications.end()) {
                                            // Not known but seen
                                            residue_modifications->Add(unknownModifications[feature_description]);
                                        }
                                        else {
                                            // Not known and not seen
                                            unknownModifications[feature_description] = new Modification(feature_description, L"unknown");
                                            residue_modifications->Add(unknownModifications[feature_description]);
                                        }
                                    }
                                    else if (feature_type == L"peptide" || feature_type == L"propeptide" || feature_type == L"chain" || feature_type == L"signal peptide") {
                                        ProteolysisProduct tempVar2(oneBasedbeginPosition, oneBasedendPosition, feature_type);
                                        proteolysisProducts.push_back(&tempVar2);
                                    }
                                    else if (feature_type == L"sequence variant" && variation_value != L"" && variation_value != L"") {
                                        if (oneBasedbeginPosition && oneBasedendPosition) {
                                            SequenceVariation tempVar3(static_cast<int>(oneBasedbeginPosition), static_cast<int>(oneBasedendPosition), original_value, variation_value, feature_description);
                                            sequenceVariations.push_back(&tempVar3);
                                        }
                                        else if (oneBasedfeature_position >= 1) {
                                            SequenceVariation tempVar4(oneBasedfeature_position, original_value, variation_value, feature_description);
                                            sequenceVariations.push_back(&tempVar4);
                                        }
                                    }
                                    else if (feature_type == L"disulfide bond") {
                                        if (oneBasedbeginPosition && oneBasedendPosition) {
                                            DisulfideBond tempVar5(static_cast<int>(oneBasedbeginPosition), static_cast<int>(oneBasedendPosition), feature_description);
                                            disulfideBonds.push_back(&tempVar5);
                                        }
                                        else if (oneBasedfeature_position >= 1) {
                                            DisulfideBond tempVar6(oneBasedfeature_position, feature_description);
                                            disulfideBonds.push_back(&tempVar6);
                                        }
                                    }
                                    oneBasedbeginPosition = std::nullopt;
                                    oneBasedendPosition = std::nullopt;
                                    oneBasedfeature_position = -1;
                                    original_value = L"";
                                    variation_value = L"";

                            }
//ORIGINAL LINE: case "dbReference":
                            else if (xml.Name == L"dbReference") {
                                    DatabaseReference tempVar7(dbReference_type, dbReference_id, Enumerable::Range(0, property_types.size())->Select([&] (std::any i) {
                                    delete substituteWhitespace;
                                        return std::tuple < std::wstring;
                                    }, std::wstring > (property_types[i], property_values[i])).ToList());
                                    databaseReferences.push_back(&tempVar7);
                                    property_types = std::vector<std::wstring>();
                                    property_values = std::vector<std::wstring>();
                                    dbReference_type = L"";
                                    dbReference_id = L"";

                            }
//ORIGINAL LINE: case "gene":
                            else if (xml.Name == L"gene") {
                                    reading_gene = false;

                            }
//ORIGINAL LINE: case "entry":
                            else if (xml.Name == L"entry") {
                                    if (accession != L"" && sequence != L"") {
                                        if (generateTargetProteins) {
                                            auto protein = new Protein(sequence, accession, gene_names, oneBasedModifications, proteolysisProducts, name, full_name, false, IsContaminant, databaseReferences, sequenceVariations, disulfideBonds, proteinDbLocation);
                                            result.push_back(protein);

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
                                        }

                                        switch (decoyType) {
                                            case DecoyType::Reverse: {
                                                std::vector<wchar_t> sequence_array = sequence.ToCharArray();
                                                std::unordered_map<int, std::vector<Modification*>> decoy_modifications;
                                                std::vector<DisulfideBond*> decoy_disulfides;
                                                if (sequence.StartsWith(L"M", StringComparison::Ordinal)) {
                                                    // Do not include the initiator methionine in reversal!!!
                                                    Array::Reverse(sequence_array, 1, sequence.length() - 1);
                                                    decoy_modifications = std::unordered_map<int, std::vector<Modification*>>(oneBasedModifications.size());
                                                    for (auto kvp : oneBasedModifications) {
                                                        if (kvp.Key > 1) {
                                                            decoy_modifications.emplace(sequence.length() - kvp.Key + 2, kvp.Value);
                                                        }
                                                        else if (kvp.Key == 1) {
                                                            decoy_modifications.emplace(1, kvp.Value);
                                                        }
                                                    }
                                                }
                                                else {
                                                    Array::Reverse(sequence_array);
                                                    decoy_modifications = std::unordered_map<int, std::vector<Modification*>>(oneBasedModifications.size());
                                                    for (auto kvp : oneBasedModifications) {
                                                        decoy_modifications.emplace(sequence.length() - kvp.Key + 1, kvp.Value);
                                                    }
                                                }
                                                auto reversed_sequence = std::wstring(sequence_array);

                                                std::vector<ProteolysisProduct*> decoyPP;
                                                for (auto pp : proteolysisProducts) {
                                                    ProteolysisProduct tempVar8(sequence.length() - pp->getOneBasedEndPosition() + 1, sequence.length() - pp->getOneBasedBeginPosition(), pp->getType());
                                                    decoyPP.push_back(&tempVar8);
                                                }
                                                for (auto disulfideBond : disulfideBonds) {
                                                    DisulfideBond tempVar9(sequence.length() - disulfideBond->getOneBasedBeginPosition() + 2, sequence.length() - disulfideBond->getOneBasedEndPosition() + 2, L"DECOY DISULFIDE BOND: " + disulfideBond->getDescription());
                                                    decoy_disulfides.push_back(&tempVar9);
                                                }

                                                std::vector<SequenceVariation*> decoy_variations;
                                                for (auto sv : sequenceVariations) {
                                                    std::vector<wchar_t> original_array = sv->getOriginalSequence().ToArray();
                                                    std::vector<wchar_t> variation_array = sv->getVariantSequence().ToArray();
                                                    if (sv->getOneBasedBeginPosition() == 1) {
                                                        bool orig_init_m = sv->getOriginalSequence().StartsWith(L"M", StringComparison::Ordinal);
                                                        bool var_init_m = sv->getVariantSequence().StartsWith(L"M", StringComparison::Ordinal);
                                                        if (orig_init_m && !var_init_m) {
                                                            SequenceVariation tempVar10(1, L"M", L"", L"DECOY VARIANT: Initiator Methionine Change in " + sv->getDescription());
                                                            decoy_variations.push_back(&tempVar10);
                                                        }
                                                        original_array = sv->getOriginalSequence().substr(static_cast<int>(orig_init_m))->ToArray();
                                                        variation_array = sv->getVariantSequence().substr(static_cast<int>(var_init_m))->ToArray();
                                                    }
                                                    int decoy_end = sequence.length() - sv->getOneBasedBeginPosition() + 2 + static_cast<int>(sv->getOneBasedEndPosition() == reversed_sequence.length()) - static_cast<int>(sv->getOneBasedBeginPosition() == 1);
                                                    int decoy_begin = decoy_end - original_array.size() + 1;
                                                    Array::Reverse(original_array);
                                                    Array::Reverse(variation_array);
                                                    SequenceVariation tempVar11(decoy_begin, decoy_end, new std::wstring(original_array), new std::wstring(variation_array), L"DECOY VARIANT: " + sv->getDescription());
                                                    decoy_variations.push_back(&tempVar11);
                                                }
                                                auto decoy_protein = new Protein(reversed_sequence, L"DECOY_" + accession, gene_names, decoy_modifications, decoyPP, name, full_name, true, IsContaminant, nullptr, decoy_variations, decoy_disulfides, proteinDbLocation);

                                                result.push_back(decoy_protein);

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein' statement was not added since decoy_protein was passed to a method or constructor. Handle memory management manually.
                                                break;

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein' statement was not added since decoy_protein was passed to a method or constructor. Handle memory management manually.
                                            }
                                            case DecoyType::Slide: {
                                                int numSlides = 20;
                                                std::vector<wchar_t> sequence_array_unslided = sequence.ToCharArray();
                                                std::vector<wchar_t> sequence_array_slided = sequence.ToCharArray();
                                                decoy_modifications = nullptr;
                                                std::vector<DisulfideBond*> decoy_disulfides_slide;
                                                if (sequence.StartsWith(L"M", StringComparison::Ordinal)) {
                                                    // Do not include the initiator methionine in shuffle!!!
                                                    if (numSlides % sequence_array_slided.size() - 1 == 0) {
                                                        numSlides++;
                                                    }
                                                    for (int i = 1; i < sequence_array_slided.size(); i++) {
                                                        sequence_array_slided[i] = sequence_array_unslided[GetOldShuffleIndex(i, numSlides, sequence.length(), true)];
                                                    }

                                                    decoy_modifications = std::unordered_map<int, std::vector<Modification*>>(oneBasedModifications.size());
                                                    for (auto kvp : oneBasedModifications) {
                                                        if (kvp.Key > 1) {
                                                            decoy_modifications->Add(GetOldShuffleIndex(kvp.Key - 1, numSlides, sequence.length(), true) + 1, kvp.Value);
                                                        }
                                                        else if (kvp.Key == 1) {
                                                            decoy_modifications->Add(1, kvp.Value);
                                                        }
                                                    }
                                                }
                                                else {
                                                    if (numSlides % sequence_array_slided.empty()) {
                                                        numSlides++;
                                                    }
                                                    for (int i = 0; i < sequence_array_slided.size(); i++) {
                                                        sequence_array_slided[i] = sequence_array_unslided[GetOldShuffleIndex(i, numSlides, sequence.length(), false)];
                                                    }
                                                    decoy_modifications = std::unordered_map<int, std::vector<Modification*>>(oneBasedModifications.size());
                                                    for (auto kvp : oneBasedModifications) {
                                                        decoy_modifications->Add(GetOldShuffleIndex(kvp.Key - 1, numSlides, sequence.length(), false) + 1, kvp.Value);
                                                    }
                                                }
                                                auto slided_sequence = std::wstring(sequence_array_slided);

                                                std::vector<ProteolysisProduct*> decoyPP_slide;
                                                for (auto pp : proteolysisProducts) { //can't keep all aa like you can with reverse, just keep it the same length
                                                    decoyPP_slide.push_back(pp);
                                                }
                                                for (auto disulfideBond : disulfideBonds) { //these actually need the same cysteines...
                                                    DisulfideBond tempVar12(GetOldShuffleIndex(disulfideBond->getOneBasedBeginPosition() - 1, numSlides, slided_sequence.length(), false) + 1, GetOldShuffleIndex(disulfideBond->getOneBasedEndPosition() - 1, numSlides, slided_sequence.length(), false) + 1, L"DECOY DISULFIDE BOND: " + disulfideBond->getDescription());
                                                    decoy_disulfides_slide.push_back(&tempVar12);
                                                }
                                                std::vector<SequenceVariation*> decoy_variations_slide;
                                                for (auto sv : sequenceVariations) { //No idea what's going on here. Review is appreciated.
                                                    std::vector<wchar_t> original_array_unshuffled = sv->getOriginalSequence().ToArray();
                                                    std::vector<wchar_t> variation_array_unslided = sv->getVariantSequence().ToArray();
                                                    if (sv->getOneBasedBeginPosition() == 1) {
                                                        bool orig_init_m = sv->getOriginalSequence().StartsWith(L"M", StringComparison::Ordinal);
                                                        bool var_init_m = sv->getVariantSequence().StartsWith(L"M", StringComparison::Ordinal);
                                                        if (orig_init_m && !var_init_m) {
                                                            SequenceVariation tempVar13(1, L"M", L"", L"DECOY VARIANT: Initiator Methionine Change in " + sv->getDescription());
                                                            decoy_variations_slide.push_back(&tempVar13);
                                                        }
                                                        original_array_unshuffled = sv->getOriginalSequence().substr(static_cast<int>(orig_init_m))->ToArray();
                                                        variation_array_unslided = sv->getVariantSequence().substr(static_cast<int>(var_init_m))->ToArray();
                                                    }
                                                    int decoy_end = sequence.length() - sv->getOneBasedBeginPosition() + 2 + static_cast<int>(sv->getOneBasedEndPosition() == slided_sequence.length()) - static_cast<int>(sv->getOneBasedBeginPosition() == 1);
                                                    int decoy_begin = decoy_end - original_array_unshuffled.size() + 1;
                                                    std::vector<wchar_t> original_array_slided = sv->getOriginalSequence().ToArray();
                                                    std::vector<wchar_t> variation_array_slided = sv->getVariantSequence().ToArray();

                                                    if (numSlides % original_array_slided.empty()) {
                                                        numSlides++;
                                                    }
                                                    for (int i = 0; i < original_array_slided.size(); i++) {
                                                        original_array_slided[i] = original_array_unshuffled[GetOldShuffleIndex(i, numSlides, original_array_unshuffled.size(), false)];
                                                    }

                                                    if (numSlides % variation_array_slided.empty()) {
                                                        numSlides++;
                                                    }
                                                    for (int i = 0; i < variation_array_slided.size(); i++) {
                                                        variation_array_slided[i] = variation_array_unslided[GetOldShuffleIndex(i, numSlides, variation_array_unslided.size(), false)];
                                                    }

                                                    SequenceVariation tempVar14(decoy_begin, decoy_end, new std::wstring(original_array_slided), new std::wstring(variation_array_slided), L"DECOY VARIANT: " + sv->getDescription());
                                                    decoy_variations_slide.push_back(&tempVar14);
                                                }
                                                auto decoy_protein_slide = new Protein(slided_sequence, L"DECOY_" + accession, gene_names, decoy_modifications, decoyPP_slide, name, full_name, true, IsContaminant, nullptr, decoy_variations_slide, decoy_disulfides_slide, proteinDbLocation);

                                                result.push_back(decoy_protein_slide);

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein_slide' statement was not added since decoy_protein_slide was passed to a method or constructor. Handle memory management manually.
                                                break;

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein_slide' statement was not added since decoy_protein_slide was passed to a method or constructor. Handle memory management manually.
                                            }
                                            default:
                                                break;
                                        }
                                    }
                                    accession = L"";
                                    name = L"";
                                    full_name = L"";
                                    sequence = L"";
                                    feature_type = L"";
                                    feature_description = L"";
                                    original_value = L"";
                                    variation_value = L"";
                                    dbReference_type = L"";
                                    dbReference_id = L"";
                                    property_types = std::vector<std::wstring>();
                                    property_values = std::vector<std::wstring>();
                                    oneBasedfeature_position = -1;
                                    oneBasedModifications = std::unordered_map<int, std::vector<Modification*>>();
                                    proteolysisProducts = std::vector<ProteolysisProduct*>();
                                    sequenceVariations = std::vector<SequenceVariation*>();
                                    disulfideBonds = std::vector<DisulfideBond*>();
                                    databaseReferences = std::vector<DatabaseReference*>();
                                    gene_names = std::vector<std::tuple<std::wstring, std::wstring>>();
                                    reading_gene = false;
                            }
                            break;
                    }
                }
            }

            delete substituteWhitespace;
        }
        return result;
    }

    std::vector<Modification*> ProteinDbLoader::GetPtmListFromProteinXml(const std::wstring &proteinDbLocation) {
        if (proteinDbLocation == last_database_location) {
            return protein_xml_modlist;
        }
        last_database_location = proteinDbLocation;

        StringBuilder *storedKnownModificationsBuilder = new StringBuilder();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new FileStream(proteinDbLocation, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
            auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
            Regex *startingWhitespace = new Regex(LR"(/^\s+/gm)");
            GZipStream tempVar(stream, CompressionMode::Decompress);
            Stream *uniprotXmlFileStream = StringHelper::endsWith(proteinDbLocation, L".gz") ? static_cast<Stream*>(&tempVar): stream;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (XmlReader xml = XmlReader.Create(uniprotXmlFileStream))
            {
                XmlReader xml = XmlReader::Create(uniprotXmlFileStream);
                while (xml.Read()) {
                    switch (xml.NodeType) {
                        case XmlNodeType::Element:
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                            switch (xml.Name)
//ORIGINAL LINE: case "modification":
                            if (xml.Name == L"modification") {
                                    std::wstring modification = startingWhitespace->Replace(xml.ReadElementString(), L"");
                                    storedKnownModificationsBuilder->appendLine(modification);

                            }
//ORIGINAL LINE: case "entry":
                            else if (xml.Name == L"entry") {
                                    if (storedKnownModificationsBuilder->length() <= 0) {
                                        protein_xml_modlist = std::vector<Modification*>();
                                    }
                                    else {
                                        protein_xml_modlist = PtmListLoader::ReadModsFromString(storedKnownModificationsBuilder->toString()).ToList<Modification*>();
                                    }

                                    delete startingWhitespace;
                                    delete storedKnownModificationsBuilder;
                                    return protein_xml_modlist;
                            }
                            break;
                    }
                }
            }

            delete startingWhitespace;
        }
        protein_xml_modlist = std::vector<Modification*>();

        delete storedKnownModificationsBuilder;
        return protein_xml_modlist;
    }

    std::vector<Protein*> ProteinDbLoader::LoadProteinFasta(const std::wstring &proteinDbLocation, bool originalTarget, DecoyType onTheFlyDecoys, bool IsContaminant, Regex *accession_expression, Regex *full_name_expression, Regex *name_expression, Regex *gene_expression) {
        std::unordered_set<std::wstring> unique_accessions;
        int unique_identifier = 1;
        std::wstring accession = L"";
        std::wstring name = L"";
        std::wstring full_name = L"";
        std::vector<std::tuple<std::wstring, std::wstring>> gene_name;

        Regex *substituteWhitespace = new Regex(LR"(\s+)");

        std::vector<Protein*> result;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new FileStream(proteinDbLocation, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
            auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
            GZipStream tempVar(stream, CompressionMode::Decompress);
            Stream *fastaFileStream = StringHelper::endsWith(proteinDbLocation, L".gz") ? static_cast<Stream*>(&tempVar): stream;

            StringBuilder *sb = nullptr;
            StreamReader *fasta = new StreamReader(fastaFileStream);

            while (true) {
                std::wstring line = fasta->ReadLine();

                if (StringHelper::startsWith(line, L">")) {
                    auto accession_match = accession_expression->Match(line);
                    auto full_name_match = full_name_expression->Match(line);
                    auto name_match = name_expression->Match(line);
                    auto gene_name_match = gene_expression->Match(line);

                    if (accession_match->Groups->Count > 1) {
                        accession = accession_expression->Match(line)->Groups[1]->Value;
                    }
                    if (full_name_match->Groups->Count > 1) {
                        full_name = full_name_expression->Match(line)->Groups[1]->Value;
                    }
                    if (name_match->Groups->Count > 1) {
                        name = name_expression->Match(line)->Groups[1]->Value;
                    }
                    if (gene_name_match->Groups->Count > 1) {
                        gene_name.push_back(std::tuple<std::wstring, std::wstring>(L"primary", gene_expression->Match(line)->Groups[1]->Value));
                    }

                    if (accession == L"" || accession == L"") {
                        accession = StringHelper::trimEnd(line.substr(1));
                    }

                    sb = new StringBuilder();
                }
                else if (sb != nullptr) {
                    sb->append(StringHelper::trim(line));
                }

                if ((fasta->Peek() == L'>' || fasta->Peek() == -1) && accession != L"" && sb != nullptr) {
                    std::wstring sequence = substituteWhitespace->Replace(sb->toString(), L"");
                    while (std::find(unique_accessions.begin(), unique_accessions.end(), accession) != unique_accessions.end()) {
                        accession += L"_" + std::to_wstring(unique_identifier);
                        unique_identifier++;
                    }
                    unique_accessions.insert(accession);
                    if (originalTarget) {
                        Protein *protein = new Protein(sequence, accession, gene_name, , , name, full_name, , IsContaminant, , , , proteinDbLocation);
                        result.push_back(protein);

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
                    }

                    switch (onTheFlyDecoys) {
                        case DecoyType::Reverse: {
                            std::vector<wchar_t> sequence_array = sequence.ToCharArray();
                            int starts_with_met = sequence.StartsWith(L"M", StringComparison::Ordinal) ? 1 : 0;
                            Array::Reverse(sequence_array, starts_with_met, sequence.length() - starts_with_met); // Do not include the initiator methionine in reversal!!!
                            auto reversed_sequence = std::wstring(sequence_array);
                            Protein *decoy_protein = new Protein(reversed_sequence, L"DECOY_" + accession, gene_name, , , name, full_name, true, IsContaminant, , , , proteinDbLocation);
                            result.push_back(decoy_protein);

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein' statement was not added since decoy_protein was passed to a method or constructor. Handle memory management manually.
                            break;

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein' statement was not added since decoy_protein was passed to a method or constructor. Handle memory management manually.
                        }
                        case DecoyType::Slide: {
                            int numSlides = 20;
                            std::vector<wchar_t> sequence_array_unslide = sequence.ToCharArray();
                            std::vector<wchar_t> sequence_array_slide = sequence.ToCharArray();
                            bool starts_with_met_slide = sequence.StartsWith(L"M", StringComparison::Ordinal);
                            for (int i = starts_with_met_slide ? 1 : 0; i < sequence.length(); i++) {
                                sequence_array_slide[i] = sequence_array_unslide[GetOldShuffleIndex(i, numSlides, sequence.length(), starts_with_met_slide)];
                            }
                            std::wstring slide_sequence = std::wstring(sequence_array_slide);
                            Protein *decoy_protein_slide = new Protein(slide_sequence, L"DECOY_" + accession, gene_name, , , name, full_name, true, IsContaminant, , , , proteinDbLocation);
                            result.push_back(decoy_protein_slide);

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein_slide' statement was not added since decoy_protein_slide was passed to a method or constructor. Handle memory management manually.
                            break;

//C# TO C++ CONVERTER TODO TASK: A 'delete decoy_protein_slide' statement was not added since decoy_protein_slide was passed to a method or constructor. Handle memory management manually.
                        }
                        default:
                            break;
                    }

                    accession = L"";
                    name = L"";
                    full_name = L"";
                    gene_name = std::vector<std::tuple<std::wstring, std::wstring>>();
                }

                // no input left
                if (fasta->Peek() == -1) {
                    break;
                }
            }

            delete fasta;
//C# TO C++ CONVERTER TODO TASK: A 'delete sb' statement was not added since sb was passed to a method or constructor. Handle memory management manually.
        }

        delete substituteWhitespace;
        return result;
    }

    std::vector<Protein*> ProteinDbLoader::Merge_proteins(std::vector<Protein*> &merge_these) {
        std::unordered_map<std::tuple<std::wstring, std::wstring, bool, bool>, std::vector<Protein*>> proteinsByAccessionSequenceContaminant;
        for (auto p : merge_these) {
            std::tuple<std::wstring, std::wstring, bool, bool> key = std::tuple<std::wstring, std::wstring, bool, bool>(p->getAccession(), p->getBaseSequence(), p->getIsContaminant(), p->getIsDecoy());
            List<Protein*> bundled;
            std::unordered_map<std::tuple<std::wstring, std::wstring, bool, bool>, std::vector<Protein*>>::const_iterator proteinsByAccessionSequenceContaminant_iterator = proteinsByAccessionSequenceContaminant.find(key);
            if (proteinsByAccessionSequenceContaminant_iterator == proteinsByAccessionSequenceContaminant.end()) {
                bundled = proteinsByAccessionSequenceContaminant_iterator->second;
                proteinsByAccessionSequenceContaminant.emplace(key, std::vector<Protein*> {p});
            }
            else {
                bundled = proteinsByAccessionSequenceContaminant_iterator->second;
                bundled->Add(p);
            }
        }

        for (auto proteins : proteinsByAccessionSequenceContaminant) {
            std::unordered_set<std::wstring> names = std::unordered_set<std::wstring>(proteins.second->Select([&] (std::any p) {
                p->Name;
            }));
            std::unordered_set<std::wstring> fullnames = std::unordered_set<std::wstring>(proteins.second->Select([&] (std::any p) {
                p->FullName;
            }));
            std::unordered_set<std::wstring> descriptions = std::unordered_set<std::wstring>(proteins.second->Select([&] (std::any p) {
                p::FullDescription;
            }));
            std::unordered_set<std::tuple<std::wstring, std::wstring>> genenames = std::unordered_set<std::tuple<std::wstring, std::wstring>>(proteins.second::SelectMany([&] (std::any p) {
                p::GeneNames;
            }));
            std::unordered_set<ProteolysisProduct*> proteolysis = std::unordered_set<ProteolysisProduct*>(proteins.second::SelectMany([&] (std::any p) {
                p::ProteolysisProducts;
            }));
            std::unordered_set<SequenceVariation*> variants = std::unordered_set<SequenceVariation*>(proteins.second::SelectMany([&] (std::any p) {
                p::SequenceVariations;
            }));
            std::unordered_set<DatabaseReference*> references = std::unordered_set<DatabaseReference*>(proteins.second::SelectMany([&] (std::any p) {
                p::DatabaseReferences;
            }));
            std::unordered_set<DisulfideBond*> bonds = std::unordered_set<DisulfideBond*>(proteins.second::SelectMany([&] (std::any p) {
                p::DisulfideBonds;
            }));

            std::unordered_map<int, std::unordered_set<Modification*>> mod_dict;
            for (auto nice : proteins.Value.SelectMany([&] (std::any p) {
                p::OneBasedPossibleLocalizedModifications;
            }).ToList()) {
                HashSet<Modification*> val;
                std::unordered_map<int, std::unordered_set<Modification*>>::const_iterator mod_dict_iterator = mod_dict.find(nice.Key);
                if (mod_dict_iterator == mod_dict.end()) {
                    val = mod_dict_iterator->second;
                    mod_dict.emplace(nice::Key, std::unordered_set<Modification*>(nice->Value));
                }
                else {
                    val = mod_dict_iterator->second;
                    for (Modification *mod : nice->Value) {
                        val->Add(mod);
                    }
                }
            }
            std::unordered_map<int, std::vector<Modification*>> mod_dict2 = mod_dict.ToDictionary([&] (std::any kv) {
                kv::Key;
            }, [&] (std::any kv) {
                kv->Value->ToList();
            });

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return new Protein(std::get<1>(proteins.first), std::get<0>(proteins.first), isContaminant: std::get<2>(proteins.first), isDecoy: std::get<3>(proteins.first), gene_names: genenames.ToList(), oneBasedModifications: mod_dict2, proteolysisProducts: proteolysis.ToList(), name: names.FirstOrDefault(), full_name: fullnames.FirstOrDefault(), databaseReferences: references.ToList(), disulfideBonds: bonds.ToList(), sequenceVariations: variants.ToList());
        }
    }

    int ProteinDbLoader::GetOldShuffleIndex(int i, int numSlides, int sequenceLength, bool methioninePresent) {
        if (methioninePresent) {
            i--;
            sequenceLength--;
        }
        bool positiveDirection = i % 2 == 0;
        int oldIndex = i;

        if (positiveDirection) {
            oldIndex += numSlides;
        }
        else {
            oldIndex -= numSlides;
        }

        while (true) {
            if (oldIndex < 0) {
                positiveDirection = true;
            }
            else if (oldIndex >= sequenceLength) {
                positiveDirection = false;
            }
            else {
                return methioninePresent ? oldIndex + 1 : oldIndex;
            }

            if (positiveDirection) {
                oldIndex = (oldIndex * -1) - 1;
            }
            else {
                oldIndex = (sequenceLength * 2) - oldIndex - 1;
            }
        }
    }

    std::unordered_map<std::wstring, std::vector<Modification*>> ProteinDbLoader::GetModificationDict(std::vector<Modification*> &mods) {
        auto mod_dict = std::unordered_map<std::wstring, std::vector<Modification*>>();
        for (auto nice : mods) {
            IList<Modification*> val;
            std::unordered_map<std::wstring, std::vector<Modification*>>::const_iterator mod_dict_iterator = mod_dict.find(nice.id);
            if (mod_dict_iterator != mod_dict.end()) {
                val = mod_dict_iterator->second;
                val->Add(nice);
            }
            else {
                val = mod_dict_iterator->second;
                mod_dict.emplace(nice->id, std::vector<Modification*> {nice});
            }
        }
        return mod_dict;
    }
}
