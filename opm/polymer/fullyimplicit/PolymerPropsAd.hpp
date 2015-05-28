/*
  Copyright 2014 SINTEF ICT, Applied Mathematics.
  Copyright 2014 STATOIL ASA.

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

#ifndef OPM_POLYMERPROPSAD_HEADED_INLCUDED
#define OPM_POLYMERPROPSAD_HEADED_INLCUDED

#include <cmath>
#include <vector>
#include <opm/autodiff/AutoDiffBlock.hpp>
#include <opm/autodiff/AutoDiffHelpers.hpp>
#include <opm/polymer/PolymerProperties.hpp>

namespace Opm {
    
    class PolymerPropsAd 
    {
    public:
		/// \return		Reference rock density.
        double rockDensity() const;
		
		/// \return 	The value of dead pore volume.
        double deadPoreVol() const;

		/// \return 	The max concentration injected.
       	double cMax() const; 

		typedef AutoDiffBlock<double> ADB;
        typedef ADB::V V;

		/// Constructor wrapping a polymer props.	
        PolymerPropsAd(const PolymerProperties& polymer_props);

		/// Destructor.
        ~PolymerPropsAd();
		
		/// \param[in] c		Array of n polymer concentraion values.
		/// \param[in] visc		Array of 2 viscosity value.
		/// \return 			value of inverse effective water viscosity.
        V 
        effectiveInvWaterVisc(const V& c,const double* visc) const;

		/// \param[in] c		Array of n polymer concentraion values.
		/// \param[in] visc		Array of 2 viscosity value 
		/// \return 			value of inverse effective water viscosity.
        ADB 
        effectiveInvWaterVisc(const ADB& c,const double* visc) const;
		
		/// \param[in] c		Array of n polymer concentraion values.
		/// \return 			Array of n mc values, here mc means m(c) * c.
        V 
        polymerWaterVelocityRatio(const V& c) const;

		/// \param[in] c		Array of n polymer concentraion values.
		/// \return 			Array of n mc values, here mc means m(c) * c.
        ADB
        polymerWaterVelocityRatio(const ADB& c) const;

		/// \param[in] c				Array of n polymer concentraion values.
		/// \param[in] cmax_cells		Array of n polymer concentraion values
		///								that the cell experienced.
		/// \return						Array of n adsorption values.
        V
        adsorption(const V& c, const V& cmax_cells) const;

		/// \param[in] c				Array of n polymer concentraion values.
		/// \param[in] cmax_cells		Array of n polymer concentraion values
		///								that the cell experienced.
		/// \return						Array of n adsorption values.
        ADB
        adsorption(const ADB& c, const ADB& cmax_cells) const;

		/// \param[in] c				Array of n polymer concentraion values.
		/// \param[in] cmax_cells		Array of n polymer concentraion values
		///								that the cell experienced.
		/// \param[in] relperm			Array of n relative water relperm values.
		/// \return						Array of n adsorption values.
        V
        effectiveRelPerm(const V& c, const V& cmax_cells, const V& relperm) const;


		/// \param[in] c				Array of n polymer concentraion values.
		/// \param[in] cmax_cells		Array of n polymer concentraion values
		///								that the cell experienced.
		/// \param[in] relperm			Array of n relative water relperm values.
		/// \return						Array of n adsorption values.
        ADB
        effectiveRelPerm(const ADB& c, const ADB& cmax_cells, const ADB& krw) const;

    private:
        const PolymerProperties& polymer_props_;
    };
    
} //namespace Opm

#endif// OPM_POLYMERPROPSAD_HEADED_INLCUDED
