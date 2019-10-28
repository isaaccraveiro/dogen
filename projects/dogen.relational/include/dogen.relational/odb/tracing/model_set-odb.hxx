// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_MODEL_SET_ODB_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_MODEL_SET_ODB_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2046500 // 2.5.0-b.15
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/pgsql/gregorian-traits.hxx>
#include <odb/boost/date-time/pgsql/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/pgsql/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20465UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen.relational/types/tracing/model_set.hpp"

#include "dogen.relational/odb/tracing/model_set_id-odb.hxx"

#include <memory>
#include <cstddef>
#include <utility>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/no-id-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // model_set
  //
  template <>
  struct class_traits< ::dogen::relational::tracing::model_set >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::dogen::relational::tracing::model_set >
  {
    public:
    typedef ::dogen::relational::tracing::model_set object_type;
    typedef ::boost::shared_ptr< ::dogen::relational::tracing::model_set > pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef void id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_id_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_id_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // model_set
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >
  {
    // id
    //
    struct id_class_
    {
      id_class_ ()
      {
      }

      // value
      //
      typedef
      pgsql::query_column<
        pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::query_type,
        pgsql::id_string >
      value_type_;

      static const value_type_ value;
    };

    static const id_class_ id;

    // qualified_name
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::std::string,
        pgsql::id_string >::query_type,
      pgsql::id_string >
    qualified_name_type_;

    static const qualified_name_type_ qualified_name;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >::id_class_::value_type_
  query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >::id_class_::
  value (A::table_name, "\"ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >::id_class_
  query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >::id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >::qualified_name_type_
  query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >::
  qualified_name (A::table_name, "\"QUALIFIED_NAME\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >:
    query_columns< ::dogen::relational::tracing::model_set, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::model_set, id_pgsql >:
    public access::object_traits< ::dogen::relational::tracing::model_set >
  {
    public:
    struct image_type
    {
      // id_
      //
      composite_value_traits< ::dogen::relational::tracing::model_set_id, id_pgsql >::image_type id_value;

      // qualified_name_
      //
      details::buffer qualified_name_value;
      std::size_t qualified_name_size;
      bool qualified_name_null;

      std::size_t version;
    };

    using object_traits<object_type>::id;

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (pgsql::bind*,
          image_type&,
          pgsql::statement_kind);

    static bool
    init (image_type&,
          const object_type&,
          pgsql::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef pgsql::no_id_object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 2UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static const char persist_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];

    public:
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::model_set, id_common >:
    public access::object_traits_impl< ::dogen::relational::tracing::model_set, id_pgsql >
  {
  };

  // model_set
  //
}

#include "dogen.relational/odb/tracing/model_set-odb.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_MODEL_SET_ODB_HXX
