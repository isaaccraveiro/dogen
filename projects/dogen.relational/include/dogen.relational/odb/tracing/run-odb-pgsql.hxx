// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_RUN_ODB_PGSQL_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_RUN_ODB_PGSQL_HXX

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

#include "dogen.relational/types/tracing/run.hpp"

#include "dogen.relational/odb/tracing/json-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/run_id-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/transform_id-odb-pgsql.hxx"

#include "dogen.relational/odb/tracing/run-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // run
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::run, id_pgsql, A >
  {
    // start
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::boost::posix_time::ptime,
        pgsql::id_timestamp >::query_type,
      pgsql::id_timestamp >
    start_type_;

    static const start_type_ start;

    // end
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::boost::posix_time::ptime,
        pgsql::id_timestamp >::query_type,
      pgsql::id_timestamp >
    end_type_;

    static const end_type_ end;

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

    // activity
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::dogen::relational::tracing::activity,
        pgsql::id_integer >::query_type,
      pgsql::id_integer >
    activity_type_;

    static const activity_type_ activity;

    // version
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::std::string,
        pgsql::id_string >::query_type,
      pgsql::id_string >
    version_type_;

    static const version_type_ version;

    // configuration
    //
    struct configuration_class_
    {
      configuration_class_ ()
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

    static const configuration_class_ configuration;

    // top_level_transform_id
    //
    struct top_level_transform_id_class_
    {
      top_level_transform_id_class_ ()
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

    static const top_level_transform_id_class_ top_level_transform_id;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::start_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::
  start (A::table_name, "\"START\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::end_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::
  end (A::table_name, "\"END\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::id_class_::value_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::id_class_::
  value (A::table_name, "\"ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::id_class_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::activity_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::
  activity (A::table_name, "\"ACTIVITY\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::version_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::
  version (A::table_name, "\"VERSION\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::configuration_class_::value_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::configuration_class_::
  value (A::table_name, "\"CONFIGURATION\"", "to_jsonb((?)::jsonb)");

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::configuration_class_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::configuration;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::top_level_transform_id_class_::value_type_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::top_level_transform_id_class_::
  value (A::table_name, "\"TOP_LEVEL_TRANSFORM_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::top_level_transform_id_class_
  query_columns< ::dogen::relational::tracing::run, id_pgsql, A >::top_level_transform_id;

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::run, id_pgsql, A >:
    query_columns< ::dogen::relational::tracing::run, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::run, id_pgsql >:
    public access::object_traits< ::dogen::relational::tracing::run >
  {
    public:
    struct id_image_type
    {
      composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::image_type id_value;

      std::size_t version;
    };

    struct image_type
    {
      // start_
      //
      long long start_value;
      bool start_null;

      // end_
      //
      long long end_value;
      bool end_null;

      // id_
      //
      composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::image_type id_value;

      // activity_
      //
      int activity_value;
      bool activity_null;

      // version_
      //
      details::buffer version_value;
      std::size_t version_size;
      bool version_null;

      // configuration_
      //
      composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::image_type configuration_value;

      // top_level_transform_id_
      //
      composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::image_type top_level_transform_id_value;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (pgsql::bind*,
          image_type&,
          pgsql::statement_kind);

    static void
    bind (pgsql::bind*, id_image_type&);

    static bool
    init (image_type&,
          const object_type&,
          pgsql::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef pgsql::object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 7UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static const char persist_statement_name[];
    static const char find_statement_name[];
    static const char update_statement_name[];
    static const char erase_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];
    static const unsigned int find_statement_types[];
    static const unsigned int update_statement_types[];

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  // run
  //
}

#include "dogen.relational/odb/tracing/run-odb-pgsql.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_RUN_ODB_PGSQL_HXX
