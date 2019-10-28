// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen.relational/odb/tracing/model_set_id-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/pgsql/traits.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/pgsql/transaction.hxx>
#include <odb/pgsql/connection.hxx>
#include <odb/pgsql/statement.hxx>
#include <odb/pgsql/statement-cache.hxx>
#include <odb/pgsql/container-statements.hxx>
#include <odb/pgsql/exceptions.hxx>

namespace odb
{
  // model_set_id
  //

  bool access::composite_value_traits< ::dogen::relational::tracing::model_set_id, id_pgsql >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // value_
    //
    if (t[0UL])
    {
      i.value_value.capacity (i.value_size);
      grew = true;
    }

    return grew;
  }

  void access::composite_value_traits< ::dogen::relational::tracing::model_set_id, id_pgsql >::
  bind (pgsql::bind* b,
        image_type& i,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (b);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    std::size_t n (0);
    ODB_POTENTIALLY_UNUSED (n);

    // value_
    //
    b[n].type = pgsql::bind::text;
    b[n].buffer = i.value_value.data ();
    b[n].capacity = i.value_value.capacity ();
    b[n].size = &i.value_size;
    b[n].is_null = &i.value_null;
    n++;
  }

  bool access::composite_value_traits< ::dogen::relational::tracing::model_set_id, id_pgsql >::
  init (image_type& i,
        const value_type& o,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // value_
    //
    {
      ::std::string const& v =
        o.value ();

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.value_value.capacity ());
      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_image (
        i.value_value,
        size,
        is_null,
        v);
      i.value_null = is_null;
      i.value_size = size;
      grew = grew || (cap != i.value_value.capacity ());
    }

    return grew;
  }

  void access::composite_value_traits< ::dogen::relational::tracing::model_set_id, id_pgsql >::
  init (value_type& o,
        const image_type&  i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // value_
    //
    {
      ::std::string& v =
        o.value ();

      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_value (
        v,
        i.value_value,
        i.value_size,
        i.value_null);
    }
  }
}

#include <odb/post.hxx>
