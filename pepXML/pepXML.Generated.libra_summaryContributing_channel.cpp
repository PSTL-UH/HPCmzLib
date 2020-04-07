#include "pepXML.Generated.libra_summaryContributing_channel.h"
#include "pepXML.Generated.libra_summaryContributing_channelAffected_channel.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<libra_summaryContributing_channelAffected_channel*> libra_summaryContributing_channel::getaffected_channel() const
        {
            return this->affected_channelField;
        }

        void libra_summaryContributing_channel::setaffected_channel(const std::vector<libra_summaryContributing_channelAffected_channel*> &value)
        {
            this->affected_channelField = value;
        }

        unsigned int libra_summaryContributing_channel::getchannel() const
        {
            return this->channelField;
        }

        void libra_summaryContributing_channel::setchannel(unsigned int value)
        {
            this->channelField = value;
        }
    }
}
