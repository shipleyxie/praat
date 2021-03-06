#ifndef _PitchTierArea_h_
#define _PitchTierArea_h_
/* PitchTierArea.h
 *
 * Copyright (C) 1992-2005,2007,2009-2012,2015-2018,2020 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "RealTierEditor.h"
#include "PitchTier.h"

#include "PitchTierArea_enums.h"

Thing_define (PitchTierArea, RealTierArea) {
	double v_minimumLegalY ()
		override { return 0.0; }
	conststring32 v_rightTickUnits ()
		override { return U" Hz"; }
	double v_defaultYmin ()
		override { return 50.0; }
	double v_defaultYmax ()
		override { return 600.0; }
	double v_valueToY (double value) override {
		const double clippedValue = Melder_clippedLeft (25.0, value);
		return our p_pitch_units == kPitchTierArea_units::HERTZ ? clippedValue : NUMhertzToSemitones (clippedValue);
	}
	double v_yToValue (double y) override {
		return our p_pitch_units == kPitchTierArea_units::HERTZ ? y : NUMsemitonesToHertz (y);
	}

	#include "PitchTierArea_prefs.h"
};

Thing_declare (PitchTierEditor);

inline static autoPitchTierArea PitchTierArea_create (FunctionEditor editor, double bottom_fraction, double top_fraction) {
	autoPitchTierArea me = Thing_new (PitchTierArea);
	FunctionArea_init (me.get(), editor, bottom_fraction, top_fraction);
	my p_pitch_units = my pref_pitch_units();
	return me;
}

/* End of file PitchTierArea.h */
#endif
