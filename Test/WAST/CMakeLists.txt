set(TEST_BIN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONFIGURATION}/Test)

add_test(conversions ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/conversions.wast)
add_test(exports ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/exports.wast)
add_test(f32 ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/f32.wast)
add_test(f64 ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/f64.wast)
add_test(fac ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/fac.wast)
add_test(float_literals ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/float_literals.wast)
add_test(float_misc ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/float_misc.wast)
add_test(forward ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/forward.wast)
add_test(hexnum ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/hexnum.wast)
add_test(i32 ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/i32.wast)
add_test(i64 ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/i64.wast)
#add_test(imports ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/imports.wast)
add_test(memory ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/memory.wast)
add_test(memory_trap ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/memory_trap.wast)
#add_test(resizing ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/resizing.wast)
add_test(runaway-recursion ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/runaway-recursion.wast)
add_test(store_retval ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/switch.wast)
add_test(switch ${TEST_BIN} ${CMAKE_CURRENT_LIST_DIR}/switch.wast)
