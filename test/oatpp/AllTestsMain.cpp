
#include "oatpp/web/FullTest.hpp"
#include "oatpp/web/FullAsyncTest.hpp"

#include "oatpp/network/virtual_/PipeTest.hpp"
#include "oatpp/network/virtual_/InterfaceTest.hpp"

#include "oatpp/core/data/share/MemoryLabelTest.hpp"

#include "oatpp/parser/json/mapping/DeserializerTest.hpp"
#include "oatpp/parser/json/mapping/DTOMapperPerfTest.hpp"
#include "oatpp/parser/json/mapping/DTOMapperTest.hpp"

#include "oatpp/encoding/UnicodeTest.hpp"
#include "oatpp/encoding/Base64Test.hpp"

#include "oatpp/core/parser/CaretTest.hpp"

#include "oatpp/core/data/mapping/type/TypeTest.hpp"
#include "oatpp/core/base/collection/LinkedListTest.hpp"
#include "oatpp/core/base/memory/MemoryPoolTest.hpp"
#include "oatpp/core/base/memory/PerfTest.hpp"
#include "oatpp/core/base/CommandLineArgumentsTest.hpp"
#include "oatpp/core/base/RegRuleTest.hpp"

#include "oatpp/core/concurrency/SpinLock.hpp"
#include "oatpp/core/base/Environment.hpp"

#include <iostream>

#ifdef OATPP_ENABLE_ALL_TESTS_MAIN
namespace {

class Logger : public oatpp::base::Logger {
private:
  oatpp::concurrency::SpinLock::Atom m_atom;
public:
  
  Logger()
  : m_atom(false)
  {}
  
  void log(v_int32 priority, const std::string& tag, const std::string& message) override {
    oatpp::concurrency::SpinLock lock(m_atom);
    std::cout << tag << ":" << message << "\n";
  }
  
};

void runTests() {
  OATPP_RUN_TEST(oatpp::test::base::RegRuleTest);
  OATPP_RUN_TEST(oatpp::test::base::CommandLineArgumentsTest);
  OATPP_RUN_TEST(oatpp::test::memory::MemoryPoolTest);
  OATPP_RUN_TEST(oatpp::test::memory::PerfTest);
  OATPP_RUN_TEST(oatpp::test::collection::LinkedListTest);
  OATPP_RUN_TEST(oatpp::test::core::data::mapping::type::TypeTest);
  OATPP_RUN_TEST(oatpp::test::parser::CaretTest);
  OATPP_RUN_TEST(oatpp::test::parser::json::mapping::DeserializerTest);
  OATPP_RUN_TEST(oatpp::test::parser::json::mapping::DTOMapperPerfTest);
  OATPP_RUN_TEST(oatpp::test::parser::json::mapping::DTOMapperTest);
  OATPP_RUN_TEST(oatpp::test::encoding::Base64Test);
  OATPP_RUN_TEST(oatpp::test::encoding::UnicodeTest);
  OATPP_RUN_TEST(oatpp::test::core::data::share::MemoryLabelTest);
  OATPP_RUN_TEST(oatpp::test::network::virtual_::PipeTest);
  OATPP_RUN_TEST(oatpp::test::network::virtual_::InterfaceTest);
  OATPP_RUN_TEST(oatpp::test::web::FullTest);
  OATPP_RUN_TEST(oatpp::test::web::FullAsyncTest);
}
  
}

int main() {
  
  oatpp::base::Environment::init();
  oatpp::base::Environment::setLogger(new Logger());
  
  runTests();
  
  oatpp::base::Environment::setLogger(nullptr);
  oatpp::base::Environment::destroy();
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);
  
  oatpp::base::Environment::destroy();
  
  return 0;
}
#endif
