#include <wasm_spec_tests.hpp>

const string wasm_str_i64_0 = base_dir + "/eosio-wasm-spec-tests/generated-tests/wasms/i64.0.wasm";
std::vector<uint8_t> wasm_i64_0= read_wasm(wasm_str_i64_0.c_str());

BOOST_DATA_TEST_CASE(i64_0_check_throw, boost::unit_test::data::xrange(0,9), index) { try {
   TESTER tester;
   tester.produce_block();
   tester.create_account( "wasmtest"_n );
   tester.produce_block();
   tester.set_code("wasmtest"_n, wasm_i64_0);
   tester.produce_block();

   action test;
   test.account = "wasmtest"_n;
   test.name = account_name((uint64_t)index);
   test.authorization = {{"wasmtest"_n, config::active_name}};

   BOOST_CHECK_THROW(push_action(tester, std::move(test), "wasmtest"_n.to_uint64_t()), wasm_execution_error);
   tester.produce_block();
} FC_LOG_AND_RETHROW() }

BOOST_DATA_TEST_CASE(i64_0_pass, boost::unit_test::data::xrange(9,13), index) { try {
   TESTER tester;
   tester.produce_block();
   tester.create_account( "wasmtest"_n );
   tester.produce_block();
   tester.set_code("wasmtest"_n, wasm_i64_0);
   tester.produce_block();

   action test;
   test.account = "wasmtest"_n;
   test.name = account_name((uint64_t)index);
   test.authorization = {{"wasmtest"_n, config::active_name}};

   push_action(tester, std::move(test), "wasmtest"_n.to_uint64_t());
   tester.produce_block();
   BOOST_REQUIRE_EQUAL( tester.validate(), true );
} FC_LOG_AND_RETHROW() }
