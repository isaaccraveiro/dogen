// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_ELEMENT_ODB_PGSQL_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_ELEMENT_ODB_PGSQL_HXX

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

#include "dogen.relational/types/tracing/element.hpp"

#include "dogen.relational/odb/tracing/element_id-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/json-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/model_id-odb-pgsql.hxx"

#include "dogen.relational/odb/tracing/element-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // element
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::element, id_pgsql, A >
  {
    // json_content
    //
    struct json_content_class_
    {
      json_content_class_ ()
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

    static const json_content_class_ json_content;

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

    // model_id
    //
    struct model_id_class_
    {
      model_id_class_ ()
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

    static const model_id_class_ model_id;

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

    // qualified_meta_name
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::std::string,
        pgsql::id_string >::query_type,
      pgsql::id_string >
    qualified_meta_name_type_;

    static const qualified_meta_name_type_ qualified_meta_name;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::json_content_class_::value_type_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::json_content_class_::
  value (A::table_name, "\"JSON_CONTENT\"", "to_jsonb((?)::jsonb)");

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::json_content_class_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::json_content;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::id_class_::value_type_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::id_class_::
  value (A::table_name, "\"ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::id_class_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::model_id_class_::value_type_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::model_id_class_::
  value (A::table_name, "\"MODEL_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::model_id_class_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::model_id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::qualified_name_type_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::
  qualified_name (A::table_name, "\"QUALIFIED_NAME\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::qualified_meta_name_type_
  query_columns< ::dogen::relational::tracing::element, id_pgsql, A >::
  qualified_meta_name (A::table_name, "\"QUALIFIED_META_NAME\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::element, id_pgsql, A >:
    query_columns< ::dogen::relational::tracing::element, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::element, id_pgsql >:
    public access::object_traits< ::dogen::relational::tracing::element >
  {
    public:
    struct image_type
    {
      // json_content_
      //
      composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::image_type json_content_value;

      // id_
      //
      composite_value_traits< ::dogen::relational::tracing::element_id, id_pgsql >::image_type id_value;

      // model_id_
      //
      composite_value_traits< ::dogen::relational::tracing::model_id, id_pgsql >::image_type model_id_value;

      // qualified_name_
      //
      details::buffer qualified_name_value;
      std::size_t qualified_name_size;
      bool qualified_name_null;

      // qualified_meta_name_
      //
      details::buffer qualified_meta_name_value;
      std::size_t qualified_meta_name_size;
      bool qualified_meta_name_null;

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

    static const std::size_t column_count = 5UL;
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

  // element
  //
}

#include "dogen.relational/odb/tracing/element-odb-pgsql.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_ELEMENT_ODB_PGSQL_HXX
