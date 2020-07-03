/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <tuple>
#include <optional>
#include <tinyxml2.h>
#include <regex>
#include <iostream>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ProteolysisProduct; }
namespace Proteomics { class SequenceVariation; }
namespace Proteomics { class DisulfideBond; }
namespace Proteomics { class SpliceSite; }
namespace Proteomics { class Modification; }
namespace Proteomics { class DatabaseReference; }
namespace Proteomics { class Protein; }
namespace Proteomics { class ModificationMotif; }

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{
	class ProteinXmlEntry
	{
		private:
			std::string privateAccession;
			std::string privateName;
			std::string privateFullName;
			std::string privateOrganism;
			std::string privateSequence;
			std::string privateFeatureType;
			std::string privateFeatureDescription;
			std::string privateSubFeatureType;
			std::string privateSubFeatureDescription;
			std::string privateOriginalValue = "";
			std::string privateVariationValue = "";
			std::string privateDBReferenceType;
			std::string privateDBReferenceId;
			std::vector<std::string> privatePropertyTypes = std::vector<std::string>();
			std::vector<std::string> privatePropertyValues = std::vector<std::string>();
			int privateOneBasedFeaturePosition = -1;
			int privateOneBasedFeatureSubPosition = -1;
			std::optional<int> privateOneBasedBeginPosition;
			std::optional<int> privateOneBasedEndPosition;
			std::vector<ProteolysisProduct*> privateProteolysisProducts = std::vector<ProteolysisProduct*>();
			std::vector<SequenceVariation*> privateSequenceVariations = std::vector<SequenceVariation*>();
			std::vector<DisulfideBond*> privateDisulfideBonds = std::vector<DisulfideBond*>();
			std::vector<SpliceSite*> privateSpliceSites = std::vector<SpliceSite*>();
			std::unordered_map<int, std::vector<Modification*>> privateOneBasedModifications = std::unordered_map<int, std::vector<Modification*>>();
			std::unordered_map<int, std::vector<Modification*>> privateOneBasedVariantModifications = std::unordered_map<int, std::vector<Modification*>>();
			std::vector<std::tuple<std::string, std::string>> privateGeneNames = std::vector<std::tuple<std::string, std::string>>();
			std::vector<DatabaseReference*> privateDatabaseReferences = std::vector<DatabaseReference*>();
			bool privateReadingGene = false;
			bool privateReadingOrganism = false;

			static std::regex *const SubstituteWhitespace;

		public:
			std::string getAccession() const;
			void setAccession(const std::string &value);
			std::string getName() const;
			void setName(const std::string &value);
			std::string getFullName() const;
			void setFullName(const std::string &value);
			std::string getOrganism() const;
			void setOrganism(const std::string &value);
			std::string getSequence() const;
			void setSequence(const std::string &value);
			std::string getFeatureType() const;
			void setFeatureType(const std::string &value);
			std::string getFeatureDescription() const;
			void setFeatureDescription(const std::string &value);
			std::string getSubFeatureType() const;
			void setSubFeatureType(const std::string &value);
			std::string getSubFeatureDescription() const;
			void setSubFeatureDescription(const std::string &value);
			std::string getOriginalValue() const;
			void setOriginalValue(const std::string &value);
			std::string getVariationValue() const;
			void setVariationValue(const std::string &value);
			std::string getDBReferenceType() const;
			void setDBReferenceType(const std::string &value);
			std::string getDBReferenceId() const;
			void setDBReferenceId(const std::string &value);
			std::vector<std::string> getPropertyTypes() const;
			void setPropertyTypes(const std::vector<std::string> &value);
			std::vector<std::string> getPropertyValues() const;
			void setPropertyValues(const std::vector<std::string> &value);
			int getOneBasedFeaturePosition() const;
			void setOneBasedFeaturePosition(int value);
			int getOneBasedFeatureSubPosition() const;
			void setOneBasedFeatureSubPosition(int value);
			std::optional<int> getOneBasedBeginPosition() const;
			void setOneBasedBeginPosition(const std::optional<int> &value);
			std::optional<int> getOneBasedEndPosition() const;
			void setOneBasedEndPosition(const std::optional<int> &value);
			std::vector<ProteolysisProduct*> getProteolysisProducts() const;
			void setProteolysisProducts(const std::vector<ProteolysisProduct*> &value);
			std::vector<SequenceVariation*> getSequenceVariations() const;
			void setSequenceVariations(const std::vector<SequenceVariation*> &value);
			std::vector<DisulfideBond*> getDisulfideBonds() const;
			void setDisulfideBonds(const std::vector<DisulfideBond*> &value);
			std::vector<SpliceSite*> getSpliceSites() const;
			void setSpliceSites(const std::vector<SpliceSite*> &value);
			std::unordered_map<int, std::vector<Modification*>> getOneBasedModifications() const;
			void setOneBasedModifications(const std::unordered_map<int, std::vector<Modification*>> &value);
			std::unordered_map<int, std::vector<Modification*>> getOneBasedVariantModifications() const;
			void setOneBasedVariantModifications(const std::unordered_map<int, std::vector<Modification*>> &value);
			std::vector<std::tuple<std::string, std::string>> getGeneNames() const;
			void setGeneNames(const std::vector<std::tuple<std::string, std::string>> &value);
			std::vector<DatabaseReference*> getDatabaseReferences() const;
			void setDatabaseReferences(const std::vector<DatabaseReference*> &value);
			bool getReadingGene() const;
			void setReadingGene(bool value);
			bool getReadingOrganism() const;
			void setReadingOrganism(bool value);

		private:
			// These lines are confusing
			// Want a look at the original C# code before implementing these two lines
			std::vector<(int, std::string)*> AnnotatedMods = std::vector<(int position, std::string originalModificationID)*>();
			std::vector<(int, std::string)*> AnnotatedVariantMods = std::vector<(int position, std::string originalModificationID)*>();

		public:
			/// <summary>
			/// Start parsing a protein XML element
			/// </summary>
			/// Original statement after c++ conversion
			/// void ParseElement(const std::string &elementName, XmlReader *xml);
			void ParseElement(const std::string &elementName, tinyxml2::XMLDocument *xml);

			/// <summary>
			/// Finish parsing at the end of an element
			/// </summary>
			/// Original statement after c++ conversion
			/// Protein *ParseEndElement(XmlReader *xml, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications, bool isContaminant, const std::string &proteinDbLocation);
			Protein *ParseEndElement(tinyxml2::XMLDocument *xml, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications, bool isContaminant, const std::string &proteinDbLocation);

			/// <summary>
			/// Finish parsing an entry
			/// </summary>
			/// Original statement after c++ conversion
			/// Protein *ParseEntryEndElement(XmlReader *xml, bool isContaminant, const std::string &proteinDbLocation, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications);
			Protein *ParseEntryEndElement(tinyxml2::XMLDocument *xml, bool isContaminant, const std::string &proteinDbLocation, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications);
			/// <summary>
			/// Finish parsing a subfeature element
			/// </summary>
			/// Original statement after c++ conversion
			/// void ParseSubFeatureEndElement(XmlReader *xml, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications);
			void ParseSubFeatureEndElement(tinyxml2::XMLDocument *xml, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications);

			/// <summary>
			/// Finish parsing a feature element
			/// </summary>
			/// Original statement after c++ conversion
			/// void ParseFeatureEndElement(XmlReader *xml, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications);
			void ParseFeatureEndElement(tinyxml2::XMLDocument *xml, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications);

		private:
			static void ParseAnnotatedMods(std::unordered_map<int, std::vector<Modification*>> &destination, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications, std::vector<std::unordered_map<int, std::string>*> &annotatedMods);

			static ModificationMotif *GetMotif(const std::string &proteinSequence, int position);

			/// <summary>
			/// Finish parsing a database reference element
			/// </summary>
			/// <param name="xml"></param>
			/// Original statement after c++ conversion
			/// void ParseDatabaseReferenceEndElement(XmlReader *xml);
			void ParseDatabaseReferenceEndElement(tinyxml2::XMLDocument *xml);

			/// <summary>
			/// Clear this object's properties
			/// </summary>
			void Clear();
	};
}
