// xml_value.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_XML_XML_VALUE_HH
# define VCSN_XML_XML_VALUE_HH

# include <vaucanson/design_pattern/element.hh>

# include <string>

namespace vcsn
{
  namespace xml
  {
    class XmlValue
    {
    protected:
      std::string v_;

    public:
      typedef std::string::iterator iterator;
      typedef std::string::const_iterator const_iterator;
      typedef std::string::reverse_iterator reverse_iterator;
      typedef std::string::const_reverse_iterator const_reverse_iterator;

      XmlValue() : v_("")
      {
      }

      XmlValue(const XmlValue& v) : v_(v.value())
      {
      }

      XmlValue(const std::string& v) : v_(v)
      {
      }

      template <typename T, typename V>
      XmlValue(const Element<T, V>& v);

      const std::string& value() const
      {
	return v_;
      }

      std::string& value()
      {
	return v_;
      }

      bool operator==(const XmlValue& v) const
      {
	return (this->v_ == v.value());
      }
    };

  }
}

# include <vaucanson/xml/xml_value.hxx>

#endif // ! VCSN_XML_XML_VALUE_HH
