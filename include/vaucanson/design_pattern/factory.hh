// factory.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_FACTORY_HH
# define VCSN_FACTORY_HH

# include <exception>
# include <map>

/**
 * @file factory.hh
 *
 * @brief Factory Method generic implementation. This code comes from
 * the proposed implementation by Alexandrescu, in his "Modern C++
 * Design" book.
 *
 * @see xml::converter, xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 **/

namespace vcsn
{

  /*--------------.
  | Error control |
  `--------------*/

  template <class IdentifierType, class ProductType>
  class DefaultFactoryError
  {
  public:
    class Exception : public std::exception
    {
    public:
      Exception(const IdentifierType& unknown_id) : unknown_id_(unknown_id) {}
      ~Exception() throw() {};
      virtual const char*	what()
      {
	return "Unknown object type passed to Factory.";
      }

      const IdentifierType	GetId()
      {
	return unknown_id_;
      }
    private:
      IdentifierType		unknown_id_;
    };

  protected:
    ProductType*		OnUnknownType(const IdentifierType& id)
    {
      throw Exception(id);
    }
  };


  /*----------------.
  | Generic Factory |
  `----------------*/

  template <
    class AbstractProduct,
    class IdentifierType,
    class ProductCreator = AbstractProduct* (*)(),
    template <typename, class> class FactoryErrorPolicy = DefaultFactoryError
  >
  class Factory : public FactoryErrorPolicy<IdentifierType, AbstractProduct>
  {
  public:
    bool			reg(const IdentifierType& id,
				    ProductCreator creator)
    {
      typedef typename assoc_map_t::value_type value_type;

      return associations_.insert(value_type(id, creator)).second;
    }


    bool			unreg(const IdentifierType& id)
    {
      return associations_.erase(id) == 1;
    }


    AbstractProduct*		create_object(const IdentifierType& id)
    {


      typename assoc_map_t::const_iterator i = associations_.find(id);

      if (i != associations_.end())
        return (i->second)();
      return OnUnknownType(id);
    }

  private:
    typedef std::map<IdentifierType, ProductCreator> assoc_map_t;
    assoc_map_t associations_;
  };

} // !vcsn


#define factory_reg(factory, typeId, creationFunction) \
	factory.reg(typeId, creationFunction)

#define factory_create(factory, typeId) \
	factory.create_object(typeId)


#endif // VCSN_FACTORY_HH
