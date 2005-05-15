// XML.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_XML_XML_HXX
# define VCSN_XML_XML_HXX

/**
 * @file XML.hxx
 *
 * XML main file. Contains the base functor to load / save XML.
 *
 * @see io::automaton_loader, io::automaton_saver
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


namespace vcsn
{
  namespace xml
  {

    template<typename Saver, typename Conv>
    void XML::operator()(std::ostream& out, const Saver& s,
			 const Conv&) const
    {
      xercesc::XMLPlatformUtils::Initialize();

      typedef typename Saver::automaton_t automaton_t;

      xml_converter<automaton_t> xc;
      xc.save(s.automaton(), out);

      xercesc::XMLPlatformUtils::Terminate();
    }


    template <typename Loader>
    void
    XML::operator()(std::istream& in, Loader& l)
    {
      xercesc::XMLPlatformUtils::Initialize();

      typedef typename Loader::automaton_t automaton_t;

      xml_converter<automaton_t> xc;
      xc.load(l.automaton(), in);

      xercesc::XMLPlatformUtils::Terminate();
    }


  } // !xml

} // !vcsn


#endif // VCSN_XML_XML_HXX
