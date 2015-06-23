# -*- mode: cmake; tab-width: 2; indent-tabs-mode: t; truncate-lines: t; compile-command: "cmake -Wdev" -*-
# vim: set filetype=cmake autoindent tabstop=2 shiftwidth=2 noexpandtab softtabstop=2 nowrap:

# This file sets up five lists:
#	MAIN_SOURCE_FILES     List of compilation units which will be included in
#	                      the library. If it isn't on this list, it won't be
#	                      part of the library. Please try to keep it sorted to
#	                      maintain sanity.
#
#	TEST_SOURCE_FILES     List of programs that will be run as unit tests.
#
#	TEST_DATA_FILES       Files from the source three that should be made
#	                      available in the corresponding location in the build
#	                      tree in order to run tests there.
#
#	EXAMPLE_SOURCE_FILES  Other programs that will be compiled as part of the
#	                      build, but which is not part of the library nor is
#	                      run as tests.
#
#	PUBLIC_HEADER_FILES   List of public header files that should be
#	                      distributed together with the library. The source
#	                      files can of course include other files than these;
#	                      you should only add to this list if the *user* of
#	                      the library needs it.

# originally generated with the command:
# find opm -name '*.c*' -printf '\t%p\n' | sort
list (APPEND MAIN_SOURCE_FILES
	opm/polymer/CompressibleTpfaPolymer.cpp
	opm/polymer/IncompTpfaPolymer.cpp
	opm/polymer/PolymerInflow.cpp
	opm/polymer/PolymerProperties.cpp
	opm/polymer/polymerUtilities.cpp
	opm/polymer/SimulatorCompressiblePolymer.cpp
	opm/polymer/SimulatorPolymer.cpp
	opm/polymer/TransportSolverTwophaseCompressiblePolymer.cpp
	opm/polymer/TransportSolverTwophasePolymer.cpp
    opm/polymer/fullyimplicit/PolymerPropsAd.cpp
    opm/polymer/fullyimplicit/FullyImplicitCompressiblePolymerSolver.cpp
	)

# originally generated with the command:
# find tests -name '*.cpp' -a ! -wholename '*/not-unit/*' -printf '\t%p\n' | sort
list (APPEND TEST_SOURCE_FILES
	)

# originally generated with the command:
# find tests -name '*.xml' -a ! -wholename '*/not-unit/*' -printf '\t%p\n' | sort
list (APPEND TEST_DATA_FILES
	)

# originally generated with the command:
# find examples -name '*.c*' -printf '\t%p\n' | sort
list (APPEND EXAMPLE_SOURCE_FILES
	examples/sim_poly2p_comp_reorder.cpp
	examples/sim_poly2p_incomp_reorder.cpp
	examples/test_singlecellsolves.cpp
    examples/sim_poly_fi2p_comp_ad.cpp
    examples/flow_polymer.cpp
	)

# programs listed here will not only be compiled, but also marked for
# installation
list (APPEND PROGRAM_SOURCE_FILES
	examples/sim_poly2p_comp_reorder.cpp
	examples/sim_poly2p_incomp_reorder.cpp
    examples/sim_poly_fi2p_comp_ad.cpp
    examples/flow_polymer.cpp
	)

# originally generated with the command:
# find opm -name '*.h*' -a ! -name '*-pch.hpp' -printf '\t%p\n' | sort
list (APPEND PUBLIC_HEADER_FILES
	opm/polymer/CompressibleTpfaPolymer.hpp
	opm/polymer/GravityColumnSolverPolymer.hpp
	opm/polymer/GravityColumnSolverPolymer_impl.hpp
	opm/polymer/IncompPropertiesDefaultPolymer.hpp
	opm/polymer/IncompTpfaPolymer.hpp
	opm/polymer/PolymerBlackoilState.hpp
	opm/polymer/PolymerInflow.hpp
	opm/polymer/PolymerProperties.hpp
	opm/polymer/PolymerState.hpp
	opm/polymer/polymerUtilities.hpp
	opm/polymer/SimulatorCompressiblePolymer.hpp
	opm/polymer/SimulatorPolymer.hpp
	opm/polymer/SinglePointUpwindTwoPhasePolymer.hpp
	opm/polymer/TransportSolverTwophaseCompressiblePolymer.hpp
	opm/polymer/Point2D.hpp
    opm/polymer/TransportSolverTwophasePolymer.hpp
    opm/polymer/fullyimplicit/PolymerPropsAd.hpp
    opm/polymer/fullyimplicit/FullyImplicitCompressiblePolymerSolver.hpp
    opm/polymer/fullyimplicit/SimulatorFullyImplicitCompressiblePolymer.hpp
    opm/polymer/fullyimplicit/SimulatorFullyImplicitCompressiblePolymer_impl.hpp
    opm/polymer/fullyimplicit/BlackoilPolymerModel.hpp
    opm/polymer/fullyimplicit/BlackoilPolymerModel_impl.hpp
    opm/polymer/fullyimplicit/SimulatorFullyImplicitBlackoilPolymer.hpp
    opm/polymer/fullyimplicit/SimulatorFullyImplicitBlackoilPolymer_impl.hpp
    opm/polymer/fullyimplicit/WellStateFullyImplicitBlackoilPolymer.hpp
	)
