// Copyright 2009-2014 Toby Schneider (https://launchpad.net/~tes)
//                     GobySoft, LLC (2013-)
//                     Massachusetts Institute of Technology (2007-2014)
//                     Goby Developers Team (https://launchpad.net/~goby-dev)
// 
//
// This file is part of the Goby Underwater Autonomy Project Libraries
// ("The Goby Libraries").
//
// The Goby Libraries are free software: you can redistribute them and/or modify
// them under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 2.1 of the License, or
// (at your option) any later version.
//
// The Goby Libraries are distributed in the hope that they will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Goby.  If not, see <http://www.gnu.org/licenses/>.



#ifndef IridiumModemDriver20130903H
#define IridiumModemDriver20130903H

#include <string>
#include <stdint.h>
#include <stdexcept>

namespace goby
{
    namespace acomms
    {
        class RudicsPacketException : public std::runtime_error
        {
          public:
          RudicsPacketException(const std::string& what)
              : std::runtime_error(what)
            { }
        };
            
        void serialize_rudics_packet(std::string bytes, std::string* rudics_pkt);
        void parse_rudics_packet(std::string* bytes, std::string rudics_pkt);
        std::string uint32_to_byte_string(uint32_t i);
        uint32_t byte_string_to_uint32(std::string s);
    }
}


#endif