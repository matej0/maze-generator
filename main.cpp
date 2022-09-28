#include "include.h"
#include "maze.h"



int main( )
{
	FreeConsole( );

	sf::RenderWindow window( sf::VideoMode( 400, 400 ), "SFML works!" );
	window.setFramerateLimit( 144 );

	api::m_render_window = &window;
	api::m_window_size_x = window.getSize( ).x; api::m_window_size_y = window.getSize( ).y;

	api::m_rows	   = std::floor( api::m_window_size_x / cell_size );
	api::m_columns = std::floor( api::m_window_size_y / cell_size );

	Maze myMaze;
	myMaze.Initialize( );

	

	while( window.isOpen( ) )
	{
		sf::Event event;
		while( window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				window.close( );
		}

		window.clear( );
		{
			myMaze.Run( );
		}
		window.display( );
	}

	return EXIT_SUCCESS;
}