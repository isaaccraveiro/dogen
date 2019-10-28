// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen.relational/odb/tracing/transform_components_key-odb.hxx"

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
  // transform_components_key
  //

  bool access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_pgsql >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // parent_id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::grow (
          i.parent_id_value, t + 0UL))
      grew = true;

    // component_id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::grow (
          i.component_id_value, t + 1UL))
      grew = true;

    return grew;
  }

  void access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_pgsql >::
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

    // parent_id_
    //
    composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::bind (
      b + n, i.parent_id_value, sk);
    n += 1UL;

    // component_id_
    //
    composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::bind (
      b + n, i.component_id_value, sk);
    n += 1UL;
  }

  bool access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_pgsql >::
  init (image_type& i,
        const value_type& o,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // parent_id_
    //
    {
      ::dogen::relational::tracing::transform_id const& v =
        o.parent_id ();

      if (composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::init (
            i.parent_id_value,
            v,
            sk))
        grew = true;
    }

    // component_id_
    //
    {
      ::dogen::relational::tracing::transform_id const& v =
        o.component_id ();

      if (composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::init (
            i.component_id_value,
            v,
            sk))
        grew = true;
    }

    return grew;
  }

  void access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_pgsql >::
  init (value_type& o,
        const image_type&  i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // parent_id_
    //
    {
      ::dogen::relational::tracing::transform_id& v =
        o.parent_id ();

      composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::init (
        v,
        i.parent_id_value,
        db);
    }

    // component_id_
    //
    {
      ::dogen::relational::tracing::transform_id& v =
        o.component_id ();

      composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::init (
        v,
        i.component_id_value,
        db);
    }
  }
}

#include <odb/post.hxx>
