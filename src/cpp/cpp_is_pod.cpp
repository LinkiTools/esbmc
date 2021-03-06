/*******************************************************************\

Module: C++ Language Type Checking

Author: Daniel Kroening, kroening@cs.cmu.edu

\*******************************************************************/

#include "cpp_typecheck.h"

/*******************************************************************\

Function: cpp_typecheckt::cpp_is_pod

  Inputs:

 Outputs:

 Standard:
  "Arithmetic types (3.9.1), enumeration types, pointer types, and
  pointer to member types (3.9.2), and cvqualified versions of
  these types (3.9.3) are collectively called scalar types. Scalar
  types, POD-struct types, POD-union types (clause 9), arrays of
  such types and cv-qualified versions of these types (3.9.3) are
  collectively called POD types."

  "A POD-struct is an aggregate class that has no non-static data
  members of type non-POD-struct, non-POD-union (or array of such
  types) or reference, and has no user-defined copy assignment
  operator and no user-defined destructor. Similarly, a POD-union
  is an aggregate union that has no non-static data members of type
  non-POD-struct, non-POD-union (or array of such types) or reference,
  and has no userdefined copy assignment operator and no user-defined
  destructor. A POD class is a class that is either a POD-struct or
  a POD-union."

  "An aggregate is an array or a class (clause 9) with no
  user-declared constructors (12.1), no private or protected
  non-static data members (clause 11), no base classes (clause 10),
  and no virtual functions (10.3)."

\*******************************************************************/

bool cpp_typecheckt::cpp_is_pod(const typet &type) const
{
  if(type.id()=="struct")
  {
    // Not allowed in PODs:
    // * Non-PODs
    // * Constructors/Destructors
    // * virtuals
    // * private/protected, unless static
    // * overloading assignment operator
    // * Base classes

    // XXX jmorse: certain things listed above don't always make their way into
    // the class definition though, such as templated constructors. In that
    // case, we set a flag to indicate that such methods have been seen, before
    // removing them. The "is_not_pod" flag thus only guarentees that it /isn't/
    // and its absence doesn't guarentee that it is.
    if (!type.find("is_not_pod").is_nil())
      return false;

    const struct_typet &struct_type=to_struct_type(type);

    if(!type.find("bases").get_sub().empty())
      return false;

    const struct_typet::componentst &components=
      struct_type.components();

    for(struct_typet::componentst::const_iterator
        it=components.begin();
        it!=components.end();
        it++)
    {
      if(it->is_type())
        continue;

      if(it->get_base_name()=="operator=")
        return false;

      if(it->get_bool("is_virtual"))
        return false;

      const typet &sub_type=it->type();

      if(sub_type.id()=="code")
      {
        if(it->get_bool("is_virtual"))
          return false;

        const typet &return_type=to_code_type(sub_type).return_type();

        if(return_type.id()=="constructor" ||
           return_type.id()=="destructor")
          return false;
      }
      else if(it->get("access") != "public" &&
              !it->get_bool("is_static"))
        return false;

      if(!cpp_is_pod(sub_type))
        return false;
    }

    return true;
  }
  else if(type.id()=="array")
  {
    return cpp_is_pod(type.subtype());
  }
  else if(type.id()=="pointer")
  {
    if(is_reference(type)) // references are not PODs
      return false;

    // but pointers are PODs!
    return true;
  }
  else if(type.id()=="symbol")
  {
    const symbolt &symb=lookup(type.identifier());
    assert(symb.is_type);
    return cpp_is_pod(symb.type);
  }

  // everything else is POD
  return true;
}
