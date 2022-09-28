#pragma once

namespace math {
	// pi constants.
	constexpr float pi = 3.1415926535897932384f; // pi
	constexpr float pi_2 = pi * 2.f;               // pi * 2

	// degrees to radians.
	__forceinline constexpr float deg_to_rad(float val) {
		return val * (pi / 180.f);
	}

	// radians to degrees.
	__forceinline constexpr float rad_to_deg(float val) {
		return val * (180.f / pi);
	}


	__forceinline float lerp(float a, float b, float f) {
		return (a * (1.0f - f)) + (b * f);
	}

	template < typename t >
	__forceinline void clamp(t& n, const t& lower, const t& upper) {
		n = std::max(lower, std::min(n, upper));
	}


};