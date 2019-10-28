// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen.relational/odb/tracing/attribute-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/pgsql/traits.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/pgsql/transaction.hxx>
#include <odb/pgsql/connection.hxx>
#include <odb/pgsql/statement.hxx>
#include <odb/pgsql/statement-cache.hxx>
#include <odb/pgsql/no-id-object-statements.hxx>
#include <odb/pgsql/container-statements.hxx>
#include <odb/pgsql/exceptions.hxx>
#include <odb/pgsql/no-id-object-result.hxx>

namespace odb
{
  // attribute
  //

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  persist_statement_name[] = "PERSIST_DOGEN_RELATIONAL_TRACING_ATTRIBUTE";

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  query_statement_name[] = "QUERY_DOGEN_RELATIONAL_TRACING_ATTRIBUTE";

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  erase_query_statement_name[] = "ERASE_QUERY_DOGEN_RELATIONAL_TRACING_ATTRIBUTE";

  const unsigned int access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  persist_statement_types[] =
  {
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::text_oid
  };

  bool access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // json_content_
    //
    if (composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::grow (
          i.json_content_value, t + 0UL))
      grew = true;

    // id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::attribute_id, id_pgsql >::grow (
          i.id_value, t + 1UL))
      grew = true;

    // element_id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::element_id, id_pgsql >::grow (
          i.element_id_value, t + 2UL))
      grew = true;

    // qualified_name_
    //
    if (t[3UL])
    {
      i.qualified_name_value.capacity (i.qualified_name_size);
      grew = true;
    }

    // qualified_meta_name_
    //
    if (t[4UL])
    {
      i.qualified_meta_name_value.capacity (i.qualified_meta_name_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  bind (pgsql::bind* b,
        image_type& i,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    std::size_t n (0);

    // json_content_
    //
    composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::bind (
      b + n, i.json_content_value, sk);
    n += 1UL;

    // id_
    //
    composite_value_traits< ::dogen::relational::tracing::attribute_id, id_pgsql >::bind (
      b + n, i.id_value, sk);
    n += 1UL;

    // element_id_
    //
    composite_value_traits< ::dogen::relational::tracing::element_id, id_pgsql >::bind (
      b + n, i.element_id_value, sk);
    n += 1UL;

    // qualified_name_
    //
    b[n].type = pgsql::bind::text;
    b[n].buffer = i.qualified_name_value.data ();
    b[n].capacity = i.qualified_name_value.capacity ();
    b[n].size = &i.qualified_name_size;
    b[n].is_null = &i.qualified_name_null;
    n++;

    // qualified_meta_name_
    //
    b[n].type = pgsql::bind::text;
    b[n].buffer = i.qualified_meta_name_value.data ();
    b[n].capacity = i.qualified_meta_name_value.capacity ();
    b[n].size = &i.qualified_meta_name_size;
    b[n].is_null = &i.qualified_meta_name_null;
    n++;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  init (image_type& i,
        const object_type& o,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // json_content_
    //
    {
      ::dogen::relational::tracing::json const& v =
        o.json_content ();

      if (composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::init (
            i.json_content_value,
            v,
            sk))
        grew = true;
    }

    // id_
    //
    {
      ::dogen::relational::tracing::attribute_id const& v =
        o.id ();

      if (composite_value_traits< ::dogen::relational::tracing::attribute_id, id_pgsql >::init (
            i.id_value,
            v,
            sk))
        grew = true;
    }

    // element_id_
    //
    {
      ::dogen::relational::tracing::element_id const& v =
        o.element_id ();

      if (composite_value_traits< ::dogen::relational::tracing::element_id, id_pgsql >::init (
            i.element_id_value,
            v,
            sk))
        grew = true;
    }

    // qualified_name_
    //
    {
      ::std::string const& v =
        o.qualified_name ();

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.qualified_name_value.capacity ());
      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_image (
        i.qualified_name_value,
        size,
        is_null,
        v);
      i.qualified_name_null = is_null;
      i.qualified_name_size = size;
      grew = grew || (cap != i.qualified_name_value.capacity ());
    }

    // qualified_meta_name_
    //
    {
      ::std::string const& v =
        o.qualified_meta_name ();

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.qualified_meta_name_value.capacity ());
      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_image (
        i.qualified_meta_name_value,
        size,
        is_null,
        v);
      i.qualified_meta_name_null = is_null;
      i.qualified_meta_name_size = size;
      grew = grew || (cap != i.qualified_meta_name_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // json_content_
    //
    {
      ::dogen::relational::tracing::json& v =
        o.json_content ();

      composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::init (
        v,
        i.json_content_value,
        db);
    }

    // id_
    //
    {
      ::dogen::relational::tracing::attribute_id& v =
        o.id ();

      composite_value_traits< ::dogen::relational::tracing::attribute_id, id_pgsql >::init (
        v,
        i.id_value,
        db);
    }

    // element_id_
    //
    {
      ::dogen::relational::tracing::element_id& v =
        o.element_id ();

      composite_value_traits< ::dogen::relational::tracing::element_id, id_pgsql >::init (
        v,
        i.element_id_value,
        db);
    }

    // qualified_name_
    //
    {
      ::std::string& v =
        o.qualified_name ();

      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_value (
        v,
        i.qualified_name_value,
        i.qualified_name_size,
        i.qualified_name_null);
    }

    // qualified_meta_name_
    //
    {
      ::std::string& v =
        o.qualified_meta_name ();

      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_value (
        v,
        i.qualified_meta_name_value,
        i.qualified_meta_name_size,
        i.qualified_meta_name_null);
    }
  }

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::persist_statement[] =
  "INSERT INTO \"DOGEN\".\"ATTRIBUTE\" "
  "(\"JSON_CONTENT\", "
  "\"ID\", "
  "\"ELEMENT_ID\", "
  "\"QUALIFIED_NAME\", "
  "\"QUALIFIED_META_NAME\") "
  "VALUES "
  "($1, $2, $3, $4, $5)";

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::query_statement[] =
  "SELECT "
  "\"DOGEN\".\"ATTRIBUTE\".\"JSON_CONTENT\", "
  "\"DOGEN\".\"ATTRIBUTE\".\"ID\", "
  "\"DOGEN\".\"ATTRIBUTE\".\"ELEMENT_ID\", "
  "\"DOGEN\".\"ATTRIBUTE\".\"QUALIFIED_NAME\", "
  "\"DOGEN\".\"ATTRIBUTE\".\"QUALIFIED_META_NAME\" "
  "FROM \"DOGEN\".\"ATTRIBUTE\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::erase_query_statement[] =
  "DELETE FROM \"DOGEN\".\"ATTRIBUTE\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::table_name[] =
  "\"DOGEN\".\"ATTRIBUTE\"";

  void access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  persist (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              obj,
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    callback (db,
              obj,
              callback_event::post_persist);
  }

  result< access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::object_type >
  access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  query (database&, const query_base_type& q)
  {
    using namespace pgsql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += " ";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        sts.connection (),
        query_statement_name,
        text,
        false,
        true,
        q.parameter_types (),
        q.parameter_count (),
        q.parameters_binding (),
        imb));

    st->execute ();
    st->deallocate ();

    shared_ptr< odb::no_id_object_result_impl<object_type> > r (
      new (shared) pgsql::no_id_object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::dogen::relational::tracing::attribute, id_pgsql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      erase_query_statement_name,
      text,
      q.parameter_types (),
      q.parameter_count (),
      q.parameters_binding ());

    return st.execute ();
  }
}

namespace odb
{
  static bool
  create_schema (database& db, unsigned short pass, bool drop)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (pass);
    ODB_POTENTIALLY_UNUSED (drop);

    if (drop)
    {
      switch (pass)
      {
        case 1:
        {
          return true;
        }
        case 2:
        {
          db.execute ("DROP TABLE IF EXISTS \"DOGEN\".\"ATTRIBUTE\" CASCADE");
          return false;
        }
      }
    }
    else
    {
      switch (pass)
      {
        case 1:
        {
          db.execute ("CREATE TABLE \"DOGEN\".\"ATTRIBUTE\" (\n"
                      "  \"JSON_CONTENT\" TEXT NOT NULL,\n"
                      "  \"ID\" TEXT NOT NULL,\n"
                      "  \"ELEMENT_ID\" TEXT NOT NULL,\n"
                      "  \"QUALIFIED_NAME\" TEXT NOT NULL,\n"
                      "  \"QUALIFIED_META_NAME\" TEXT NOT NULL)");
          return false;
        }
      }
    }

    return false;
  }

  static const schema_catalog_create_entry
  create_schema_entry_ (
    id_pgsql,
    "",
    &create_schema);
}

#include <odb/post.hxx>
