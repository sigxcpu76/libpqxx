/** Implementation of libpqxx exception classes.
 *
 * Copyright (c) 2000-2020, Jeroen T. Vermeulen.
 *
 * See COPYING for copyright license.  If you did not receive a file called
 * COPYING with this source code, please notify the distributor of this
 * mistake, or contact the author.
 */
#include "pqxx-source.hxx"

#include "pqxx/except"


pqxx::failure::failure(std::string const &whatarg) :
        std::runtime_error{whatarg}
{}


pqxx::broken_connection::broken_connection() :
        failure{"Connection to database failed."}
{}


pqxx::broken_connection::broken_connection(std::string const &whatarg) :
        failure{whatarg}
{}


pqxx::sql_error::sql_error(
  std::string const &whatarg, std::string const &Q, char const sqlstate[]) :
        failure{whatarg},
        m_query{Q},
        m_sqlstate{sqlstate ? sqlstate : ""}
{}


pqxx::sql_error::~sql_error() noexcept = default;


PQXX_PURE std::string const &pqxx::sql_error::query() const noexcept
{
  return m_query;
}


PQXX_PURE std::string const &pqxx::sql_error::sqlstate() const noexcept
{
  return m_sqlstate;
}


pqxx::in_doubt_error::in_doubt_error(std::string const &whatarg) :
        failure{whatarg}
{}


pqxx::transaction_rollback::transaction_rollback(std::string const &whatarg) :
        failure{whatarg}
{}


pqxx::serialization_failure::serialization_failure(
  std::string const &whatarg) :
        transaction_rollback{whatarg}
{}


pqxx::statement_completion_unknown::statement_completion_unknown(
  std::string const &whatarg) :
        transaction_rollback{whatarg}
{}


pqxx::deadlock_detected::deadlock_detected(std::string const &whatarg) :
        transaction_rollback{whatarg}
{}


pqxx::internal_error::internal_error(std::string const &whatarg) :
        std::logic_error{"libpqxx internal error: " + whatarg}
{}


pqxx::usage_error::usage_error(std::string const &whatarg) :
        std::logic_error{whatarg}
{}


pqxx::argument_error::argument_error(std::string const &whatarg) :
        invalid_argument{whatarg}
{}


pqxx::conversion_error::conversion_error(std::string const &whatarg) :
        domain_error{whatarg}
{}


pqxx::conversion_overrun::conversion_overrun(std::string const &whatarg) :
        conversion_error{whatarg}
{}


pqxx::range_error::range_error(std::string const &whatarg) :
        out_of_range{whatarg}
{}
