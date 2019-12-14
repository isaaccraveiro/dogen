// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen.relational/odb/tracing/run_event-odb-sqlite.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/sqlite/traits.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/transaction.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/statement.hxx>
#include <odb/sqlite/statement-cache.hxx>
#include <odb/sqlite/simple-object-statements.hxx>
#include <odb/sqlite/container-statements.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/simple-object-result.hxx>

namespace odb
{
  // run_event
  //

  struct access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::extra_statement_cache_type
  {
    extra_statement_cache_type (
      sqlite::connection&,
      image_type&,
      id_image_type&,
      sqlite::binding&,
      sqlite::binding&)
    {
    }
  };

  access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::id_type
  access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  id (const image_type& i)
  {
    sqlite::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::init (
        id,
        i.run_event_key_value,
        db);
    }

    return id;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // timestamp_
    //
    if (t[0UL])
    {
      i.timestamp_value.capacity (i.timestamp_size);
      grew = true;
    }

    // run_event_key_
    //
    if (composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::grow (
          i.run_event_key_value, t + 1UL))
      grew = true;

    // version_
    //
    if (t[3UL])
    {
      i.version_value.capacity (i.version_size);
      grew = true;
    }

    // payload_
    //
    if (composite_value_traits< ::dogen::relational::tracing::json, id_sqlite >::grow (
          i.payload_value, t + 4UL))
      grew = true;

    // activity_
    //
    t[5UL] = false;

    // logging_impact_
    //
    if (t[6UL])
    {
      i.logging_impact_value.capacity (i.logging_impact_size);
      grew = true;
    }

    // tracing_impact_
    //
    if (t[7UL])
    {
      i.tracing_impact_value.capacity (i.tracing_impact_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  bind (sqlite::bind* b,
        image_type& i,
        sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    std::size_t n (0);

    // timestamp_
    //
    b[n].type = sqlite::image_traits<
      ::boost::posix_time::ptime,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.timestamp_value.data ();
    b[n].size = &i.timestamp_size;
    b[n].capacity = i.timestamp_value.capacity ();
    b[n].is_null = &i.timestamp_null;
    n++;

    // run_event_key_
    //
    if (sk != statement_update)
    {
      composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::bind (
        b + n, i.run_event_key_value, sk);
      n += 2UL;
    }

    // version_
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.version_value.data ();
    b[n].size = &i.version_size;
    b[n].capacity = i.version_value.capacity ();
    b[n].is_null = &i.version_null;
    n++;

    // payload_
    //
    composite_value_traits< ::dogen::relational::tracing::json, id_sqlite >::bind (
      b + n, i.payload_value, sk);
    n += 1UL;

    // activity_
    //
    b[n].type = sqlite::bind::integer;
    b[n].buffer = &i.activity_value;
    b[n].is_null = &i.activity_null;
    n++;

    // logging_impact_
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.logging_impact_value.data ();
    b[n].size = &i.logging_impact_size;
    b[n].capacity = i.logging_impact_value.capacity ();
    b[n].is_null = &i.logging_impact_null;
    n++;

    // tracing_impact_
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.tracing_impact_value.data ();
    b[n].size = &i.tracing_impact_size;
    b[n].capacity = i.tracing_impact_value.capacity ();
    b[n].is_null = &i.tracing_impact_null;
    n++;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  bind (sqlite::bind* b, id_image_type& i)
  {
    std::size_t n (0);
    sqlite::statement_kind sk (sqlite::statement_select);
    composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::bind (
      b + n, i.id_value, sk);
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  init (image_type& i,
        const object_type& o,
        sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    bool grew (false);

    // timestamp_
    //
    {
      ::boost::posix_time::ptime const& v =
        o.timestamp ();

      bool is_null (true);
      std::size_t cap (i.timestamp_value.capacity ());
      sqlite::value_traits<
          ::boost::posix_time::ptime,
          sqlite::id_text >::set_image (
        i.timestamp_value,
        i.timestamp_size,
        is_null,
        v);
      i.timestamp_null = is_null;
      grew = grew || (cap != i.timestamp_value.capacity ());
    }

    // run_event_key_
    //
    if (sk == statement_insert)
    {
      ::dogen::relational::tracing::run_event_key const& v =
        o.run_event_key ();

      if (composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::init (
            i.run_event_key_value,
            v,
            sk))
        grew = true;
    }

    // version_
    //
    {
      ::std::string const& v =
        o.version ();

      bool is_null (false);
      std::size_t cap (i.version_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i.version_value,
        i.version_size,
        is_null,
        v);
      i.version_null = is_null;
      grew = grew || (cap != i.version_value.capacity ());
    }

    // payload_
    //
    {
      ::dogen::relational::tracing::json const& v =
        o.payload ();

      if (composite_value_traits< ::dogen::relational::tracing::json, id_sqlite >::init (
            i.payload_value,
            v,
            sk))
        grew = true;
    }

    // activity_
    //
    {
      ::dogen::relational::tracing::activity const& v =
        o.activity ();

      bool is_null (false);
      sqlite::value_traits<
          ::dogen::relational::tracing::activity,
          sqlite::id_integer >::set_image (
        i.activity_value,
        is_null,
        v);
      i.activity_null = is_null;
    }

    // logging_impact_
    //
    {
      ::std::string const& v =
        o.logging_impact ();

      bool is_null (false);
      std::size_t cap (i.logging_impact_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i.logging_impact_value,
        i.logging_impact_size,
        is_null,
        v);
      i.logging_impact_null = is_null;
      grew = grew || (cap != i.logging_impact_value.capacity ());
    }

    // tracing_impact_
    //
    {
      ::std::string const& v =
        o.tracing_impact ();

      bool is_null (false);
      std::size_t cap (i.tracing_impact_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i.tracing_impact_value,
        i.tracing_impact_size,
        is_null,
        v);
      i.tracing_impact_null = is_null;
      grew = grew || (cap != i.tracing_impact_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // timestamp_
    //
    {
      ::boost::posix_time::ptime& v =
        o.timestamp ();

      sqlite::value_traits<
          ::boost::posix_time::ptime,
          sqlite::id_text >::set_value (
        v,
        i.timestamp_value,
        i.timestamp_size,
        i.timestamp_null);
    }

    // run_event_key_
    //
    {
      ::dogen::relational::tracing::run_event_key& v =
        o.run_event_key ();

      composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::init (
        v,
        i.run_event_key_value,
        db);
    }

    // version_
    //
    {
      ::std::string& v =
        o.version ();

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i.version_value,
        i.version_size,
        i.version_null);
    }

    // payload_
    //
    {
      ::dogen::relational::tracing::json& v =
        o.payload ();

      composite_value_traits< ::dogen::relational::tracing::json, id_sqlite >::init (
        v,
        i.payload_value,
        db);
    }

    // activity_
    //
    {
      ::dogen::relational::tracing::activity v;

      sqlite::value_traits<
          ::dogen::relational::tracing::activity,
          sqlite::id_integer >::set_value (
        v,
        i.activity_value,
        i.activity_null);

      o.activity (v);
    }

    // logging_impact_
    //
    {
      ::std::string& v =
        o.logging_impact ();

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i.logging_impact_value,
        i.logging_impact_size,
        i.logging_impact_null);
    }

    // tracing_impact_
    //
    {
      ::std::string& v =
        o.tracing_impact ();

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i.tracing_impact_value,
        i.tracing_impact_size,
        i.tracing_impact_null);
    }
  }

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  init (id_image_type& i, const id_type& id)
  {
    bool grew (false);
    sqlite::statement_kind sk (sqlite::statement_select);
    {
      if (composite_value_traits< ::dogen::relational::tracing::run_event_key, id_sqlite >::init (
            i.id_value,
            id,
            sk))
        grew = true;
    }

    if (grew)
      i.version++;
  }

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::persist_statement[] =
  "INSERT INTO \"DOGEN\".\"RUN_EVENT\" "
  "(\"TIMESTAMP\", "
  "\"RUN_ID\", "
  "\"EVENT_TYPE\", "
  "\"VERSION\", "
  "\"PAYLOAD\", "
  "\"ACTIVITY\", "
  "\"LOGGING_IMPACT\", "
  "\"TRACING_IMPACT\") "
  "VALUES "
  "(?, ?, ?, ?, ?, ?, ?, ?)";

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::find_statement[] =
  "SELECT "
  "\"DOGEN\".\"RUN_EVENT\".\"TIMESTAMP\", "
  "\"DOGEN\".\"RUN_EVENT\".\"RUN_ID\", "
  "\"DOGEN\".\"RUN_EVENT\".\"EVENT_TYPE\", "
  "\"DOGEN\".\"RUN_EVENT\".\"VERSION\", "
  "\"DOGEN\".\"RUN_EVENT\".\"PAYLOAD\", "
  "\"DOGEN\".\"RUN_EVENT\".\"ACTIVITY\", "
  "\"DOGEN\".\"RUN_EVENT\".\"LOGGING_IMPACT\", "
  "\"DOGEN\".\"RUN_EVENT\".\"TRACING_IMPACT\" "
  "FROM \"DOGEN\".\"RUN_EVENT\" "
  "WHERE \"DOGEN\".\"RUN_EVENT\".\"RUN_ID\"=? AND \"DOGEN\".\"RUN_EVENT\".\"EVENT_TYPE\"=?";

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::update_statement[] =
  "UPDATE \"DOGEN\".\"RUN_EVENT\" "
  "SET "
  "\"TIMESTAMP\"=?, "
  "\"VERSION\"=?, "
  "\"PAYLOAD\"=?, "
  "\"ACTIVITY\"=?, "
  "\"LOGGING_IMPACT\"=?, "
  "\"TRACING_IMPACT\"=? "
  "WHERE \"RUN_ID\"=? AND \"EVENT_TYPE\"=?";

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::erase_statement[] =
  "DELETE FROM \"DOGEN\".\"RUN_EVENT\" "
  "WHERE \"RUN_ID\"=? AND \"EVENT_TYPE\"=?";

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::query_statement[] =
  "SELECT "
  "\"DOGEN\".\"RUN_EVENT\".\"TIMESTAMP\", "
  "\"DOGEN\".\"RUN_EVENT\".\"RUN_ID\", "
  "\"DOGEN\".\"RUN_EVENT\".\"EVENT_TYPE\", "
  "\"DOGEN\".\"RUN_EVENT\".\"VERSION\", "
  "\"DOGEN\".\"RUN_EVENT\".\"PAYLOAD\", "
  "\"DOGEN\".\"RUN_EVENT\".\"ACTIVITY\", "
  "\"DOGEN\".\"RUN_EVENT\".\"LOGGING_IMPACT\", "
  "\"DOGEN\".\"RUN_EVENT\".\"TRACING_IMPACT\" "
  "FROM \"DOGEN\".\"RUN_EVENT\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::erase_query_statement[] =
  "DELETE FROM \"DOGEN\".\"RUN_EVENT\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::table_name[] =
  "\"DOGEN\".\"RUN_EVENT\"";

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  persist (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
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

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace sqlite;
    using sqlite::update_statement;

    callback (db, obj, callback_event::pre_update);

    sqlite::transaction& tr (sqlite::transaction::current ());
    sqlite::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& idi (sts.id_image ());
    init (idi, id (obj));

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (idi.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (idi.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, idi);
        sts.id_image_version (idi.version);
        idb.version++;
      }

      sts.update_id_image_version (idi.version);

      if (!u)
        imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  erase (database& db, const id_type& id)
  {
    using namespace sqlite;

    ODB_POTENTIALLY_UNUSED (db);

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::pointer_type
  access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  find (database& db, const id_type& id)
  {
    using namespace sqlite;

    {
      pointer_type p (pointer_cache_traits::find (db, id));

      if (!pointer_traits::null_ptr (p))
        return p;
    }

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory<object_type, pointer_type>::create ());
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, p));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement ());
      ODB_POTENTIALLY_UNUSED (st);

      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);
      sts.load_delayed (0);
      l.unlock ();
      callback (db, obj, callback_event::post_load);
      pointer_cache_traits::load (ig.position ());
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);
    assert (l.locked ()) /* Must be a top-level call. */;

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  reload (database& db, object_type& obj)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);
    assert (l.locked ()) /* Must be a top-level call. */;

    const id_type& id (object_traits_impl::id (obj));
    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  find_ (statements_type& sts,
         const id_type* id)
  {
    using namespace sqlite;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  result< access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::object_type >
  access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  query (database&, const query_base_type& q)
  {
    using namespace sqlite;
    using odb::details::shared;
    using odb::details::shared_ptr;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());

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
        conn,
        text,
        false,
        true,
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) sqlite::object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::dogen::relational::tracing::run_event, id_sqlite >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      text,
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
          db.execute ("DROP TABLE IF EXISTS \"DOGEN\".\"RUN_EVENT\"");
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
          db.execute ("CREATE TABLE \"DOGEN\".\"RUN_EVENT\" (\n"
                      "  \"TIMESTAMP\" TEXT NULL,\n"
                      "  \"RUN_ID\" TEXT NOT NULL,\n"
                      "  \"EVENT_TYPE\" INTEGER NOT NULL,\n"
                      "  \"VERSION\" TEXT NOT NULL,\n"
                      "  \"PAYLOAD\" TEXT NOT NULL,\n"
                      "  \"ACTIVITY\" INTEGER NOT NULL,\n"
                      "  \"LOGGING_IMPACT\" TEXT NOT NULL,\n"
                      "  \"TRACING_IMPACT\" TEXT NOT NULL,\n"
                      "  PRIMARY KEY (\"RUN_ID\",\n"
                      "               \"EVENT_TYPE\"))");
          return false;
        }
      }
    }

    return false;
  }

  static const schema_catalog_create_entry
  create_schema_entry_ (
    id_sqlite,
    "",
    &create_schema);
}

#include <odb/post.hxx>
