#ifndef UNIFAQ_LIBRARY_H
#define UNIFAQ_LIBRARY_H

#include <vector>
#include <exception>

#include "rapidjson/rapidjson.h"
#include "rapidjson/Document.h"

namespace UNIFAQLibrary{

    /// A structure containing references for a single group (its multiplicity, main group index, etc.)
    struct Group{
        int sgi, ///< Sub group index
            mgi; ///< Main group index
        double R_k, ///< R_k
            Q_k; ///< Q_k
    };

    struct InteractionParameters{
        int mgi1, ///< The first main group index
            mgi2; ///< The second main group index
        double a_ij, ///< 
               a_ji, ///< 
               b_ij, ///< 
               b_ji, ///< 
               c_ij, ///< 
               c_ji; ///< 
        /// Swap a_ij with a_ji, b_ij with b_ji, etc.
        void swap() {
            std::swap(a_ij, a_ji);
            std::swap(b_ij, b_ji);
            std::swap(c_ij, c_ji);
        }
    };

    /// A structure containing the group decomposition for a given fluid
    struct Component{
        std::vector<Group> groups; ///< The collection of groups forming the component from the group decomposition
    };

    struct UNIFAQParameterLibrary{
    private:
        std::vector<Group> groups; ///< The collection of groups forming the component from the group decomposition
        std::vector<InteractionParameters> interaction_parameters; ///< The collection of interaction parameters between main groups in the library

        /// Convert string to JSON document
        rapidjson::Document jsonize(std::string &s);
        /// Populate internal data structures based on rapidjson Documents
        void populate(rapidjson::Value &group_data, rapidjson::Value &interaction_data);
    public:
        /// Populate internal data structures based on rapidjson Documents
        void populate(std::string &group_data, std::string &interaction_data);
        /// Get the data for group with given sub group index
        Group get_group(int sgi);
        /// Get the interaction parameters for given mgi-mgi pair
        InteractionParameters get_interaction_parameters(int mgi1, int mgi2);
    };

}; /* namespace UNIFAQLibrary*/

#endif