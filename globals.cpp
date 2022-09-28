#include "include.h"
//i hate c++

namespace api {
	void* m_render_window;
	int m_window_size_x;
	int m_window_size_y;
	int m_columns;
	int m_rows;

	int random_int( int min, int max )
	{
		std::random_device                  Device;
		std::mt19937                        Generator( Device( ) );
		std::uniform_int_distribution<int>    Distr( min, max );

		return Distr( Generator );
	};

};