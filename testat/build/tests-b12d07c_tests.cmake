add_test( [==[JSON-Parsing für fuelprices]==] /workspaces/tfe23-2/testat/build/tests [==[JSON-Parsing für fuelprices]==]  )
set_tests_properties( [==[JSON-Parsing für fuelprices]==] PROPERTIES WORKING_DIRECTORY /workspaces/tfe23-2/testat/build)
add_test( [==[Station Details JSON-Parsing]==] /workspaces/tfe23-2/testat/build/tests [==[Station Details JSON-Parsing]==]  )
set_tests_properties( [==[Station Details JSON-Parsing]==] PROPERTIES WORKING_DIRECTORY /workspaces/tfe23-2/testat/build)
set( tests_TESTS [==[JSON-Parsing für fuelprices]==] [==[Station Details JSON-Parsing]==])
