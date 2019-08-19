set(TEST_SUITE
    test_matrix
    test_vector
    test_nn
    test_parser
    test_train_nn
    test_random
)

foreach(test ${TEST_SUITE})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} NN)
    add_test(${test} ${test})
endforeach()

add_custom_target(tests DEPENDS ${TEST_SUITE})
