/*
  Copyright 2012 SINTEF ICT, Applied Mathematics.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPM_POLYMERUTILITIES_HEADER_INCLUDED
#define OPM_POLYMERUTILITIES_HEADER_INCLUDED


#include <opm/core/grid.h>
#include <opm/core/fluid/IncompPropertiesInterface.hpp>
#include <opm/core/fluid/BlackoilPropertiesInterface.hpp>
#include <opm/polymer/PolymerProperties.hpp>
#include <opm/polymer/PolymerState.hpp>
#include <opm/polymer/PolymerBlackoilState.hpp>
#include <opm/core/fluid/RockCompressibility.hpp>
#include <opm/core/utility/SparseVector.hpp>
#include <vector>


namespace Opm
{

    /// @brief Computes total mobility for a set of s/c values.
    /// @param[in]  props     rock and fluid properties
    /// @param[in]  polyprops polymer properties
    /// @param[in]  cells     cells with which the saturation values are associated
    /// @param[in]  s         saturation values (for all phases)
    /// @param[in]  c         polymer concentration
    /// @param[out] totmob    total mobilities.
    void computeTotalMobility(const Opm::IncompPropertiesInterface& props,
			      const Opm::PolymerProperties& polyprops,
			      const std::vector<int>& cells,
			      const std::vector<double>& s,
			      const std::vector<double>& c,
			      const std::vector<double>& cmax,
			      std::vector<double>& totmob);

    /// @brief Computes total mobility and omega for a set of s/c values.
    /// @param[in]  props     rock and fluid properties
    /// @param[in]  polyprops polymer properties
    /// @param[in]  cells     cells with which the saturation values are associated
    /// @param[in]  s         saturation values (for all phases)
    /// @param[in]  c         polymer concentration
    /// @param[out] totmob    total mobility
    /// @param[out] omega     mobility-weighted (or fractional-flow weighted)
    ///                       fluid densities.
    void computeTotalMobilityOmega(const Opm::IncompPropertiesInterface& props,
				   const Opm::PolymerProperties& polyprops,
				   const std::vector<int>& cells,
				   const std::vector<double>& s,
				   const std::vector<double>& c,
                                   const std::vector<double>& cmax,
				   std::vector<double>& totmob,
				   std::vector<double>& omega);

    /// @brief Computes injected and produced volumes of all phases,
    ///        and injected and produced polymer mass.
    /// Note 1: assumes that only the first phase is injected.
    /// Note 2: assumes that transport has been done with an
    ///         implicit method, i.e. that the current state
    ///         gives the mobilities used for the preceding timestep.
    /// @param[in]  props     fluid and rock properties.
    /// @param[in]  polyprops polymer properties
    /// @param[in]  state     state variables (pressure, fluxes etc.)
    /// @param[in]  src       if < 0: total reservoir volume outflow,
    ///                       if > 0: first phase reservoir volume inflow.
    /// @param[in]  inj_c     injected concentration by cell
    /// @param[in]  dt        timestep used
    /// @param[out] injected  must point to a valid array with P elements,
    ///                       where P = s.size()/src.size().
    /// @param[out] produced  must also point to a valid array with P elements.
    /// @param[out] polyinj   injected mass of polymer
    /// @param[out] polyprod  produced mass of polymer
    void computeInjectedProduced(const IncompPropertiesInterface& props,
                                 const Opm::PolymerProperties& polyprops,
                                 const PolymerState& state,
				 const std::vector<double>& transport_src,
				 const std::vector<double>& inj_c,
				 const double dt,
				 double* injected,
				 double* produced,
                                 double& polyinj,
                                 double& polyprod);

    /// @brief Computes injected and produced volumes of all phases,
    ///        and injected and produced polymer mass - in the compressible case.
    /// Note 1: assumes that only the first phase is injected.
    /// Note 2: assumes that transport has been done with an
    ///         implicit method, i.e. that the current state
    ///         gives the mobilities used for the preceding timestep.
    /// @param[in]  props     fluid and rock properties.
    /// @param[in]  polyprops polymer properties
    /// @param[in]  state     state variables (pressure, fluxes etc.)
    /// @param[in]  src       if < 0: total reservoir volume outflow,
    ///                       if > 0: first phase *surface volume* inflow.
    /// @param[in]  inj_c     injected concentration by cell
    /// @param[in]  dt        timestep used
    /// @param[out] injected  must point to a valid array with P elements,
    ///                       where P = s.size()/src.size().
    /// @param[out] produced  must also point to a valid array with P elements.
    /// @param[out] polyinj   injected mass of polymer
    /// @param[out] polyprod  produced mass of polymer
    void computeInjectedProduced(const BlackoilPropertiesInterface& props,
                                 const Opm::PolymerProperties& polyprops,
                                 const PolymerBlackoilState& state,
				 const std::vector<double>& transport_src,
				 const std::vector<double>& inj_c,
				 const double dt,
                                 double* injected,
                                 double* produced,
                                 double& polyinj,
                                 double& polyprod);

    /// @brief Computes total (free) polymer mass over all grid cells.
    /// @param[in]  pv        the pore volume by cell.
    /// @param[in]  s         saturation values (for all P phases)
    /// @param[in]  c         polymer concentration
    /// @param[in]  dps       dead pore space
    /// @return               total polymer mass in grid.
    double computePolymerMass(const std::vector<double>& pv,
                              const std::vector<double>& s,
                              const std::vector<double>& c,
                              const double dps);

    /// @brief Computes total absorbed polymer mass over all grid cells.
    /// @param[in]  props     fluid and rock properties.
    /// @param[in]  polyprops polymer properties
    /// @param[in]  pv        the pore volume by cell.
    /// @param[in]  cmax      max polymer concentration for cell
    /// @return               total absorbed polymer mass.
    double computePolymerAdsorbed(const IncompPropertiesInterface& props,
                                  const Opm::PolymerProperties& polyprops,
                                  const std::vector<double>& pv,
                                  const std::vector<double>& cmax);

    /// @brief Computes total absorbed polymer mass over all grid cells.
    /// With compressibility
    /// @param[in]  grid      grid
    /// @param[in]  props     fluid and rock properties.
    /// @param[in]  polyprops polymer properties
    /// @param[in]  state     State variables
    /// @param[in]  rock_comp Rock compressibility (optional)
    /// @return               total absorbed polymer mass.
    double computePolymerAdsorbed(const UnstructuredGrid& grid,
                                  const BlackoilPropertiesInterface& props,
                                  const Opm::PolymerProperties& polyprops,
                                  const PolymerBlackoilState& state,
                                  const RockCompressibility* rock_comp);




} // namespace Opm


#endif // OPM_POLYMERUTILITIES_HEADER_INCLUDED
