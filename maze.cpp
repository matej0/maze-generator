#include "maze.h"


Cell::Cell( int x, int y ) {

	sf::RectangleShape* top = new sf::RectangleShape( );

	top->setSize( sf::Vector2f( cell_size, 1.f ) );
	top->setPosition( { static_cast< float >( x ) * cell_size, static_cast< float >( y ) * cell_size } );
	top->setFillColor( sf::Color::White );

	m_vertices.push_back( { top, true } );

	sf::RectangleShape* right = new sf::RectangleShape( );

	right->setSize( sf::Vector2f( 1.f, cell_size ) );
	right->setPosition( { (static_cast< float >( x ) * cell_size) + cell_size, static_cast< float >( y ) * cell_size } );
	right->setFillColor( sf::Color::White );

	m_vertices.push_back( { right, true } );

	sf::RectangleShape* bottom = new sf::RectangleShape( );

	bottom->setSize( sf::Vector2f( cell_size, 1.f ) );
	bottom->setPosition( { static_cast< float >( x ) * cell_size, (static_cast< float >( y ) * cell_size) + cell_size } );
	bottom->setFillColor( sf::Color::White );

	m_vertices.push_back( { bottom, true } );

	sf::RectangleShape* left = new sf::RectangleShape( );

	left->setSize( sf::Vector2f( 1.f, cell_size ) );
	left->setPosition( { static_cast< float >( x ) * cell_size , static_cast< float >( y ) * cell_size } );
	left->setFillColor( sf::Color::White );

	m_vertices.push_back( { left, true } );
}

void Cell::RemoveWall( int wall ) {
	if( !this || this->m_vertices.empty( ) )
		return;

	this->m_vertices[ wall ].m_should_draw = false;
}

void Maze::CreateCells( ) {

	for( int i = 0; i < api::m_rows; i++ ) {
		for( int j = 0; j < api::m_columns; j++ ) {

			Cell* cell = new Cell( j, i );

			// each cell should keep track of its own location on the grid.
			cell->m_index_row = i;
			cell->m_index_column = j;

			m_cells.push_back( cell );
			m_grid[ i ][ j ] = cell;
		}
	}
}


// i = row, j = column.
Cell* Maze::GetCell( int i, int j ) {
	return m_grid[ i ][ j ];
}

void Maze::IndexCells( ) {

	int idx = 0;

	if( m_cells.empty( ) )
		return;

	for( auto it : m_cells ) {
		if( !it )
			continue;

		it->m_index = idx;
		idx++;
	}
}

void Maze::FindNeighboringCells( ) {

	if( m_cells.empty( ) )
		return;

	for( auto it : m_cells ) {
		if( !it )
			continue;

		int col = it->m_index_column;
		int row = it->m_index_row;
		int idx = it->m_index;

		Cell* down  = m_grid[ row + 1 ][ col ];
		Cell* up	= m_grid[ row - 1 ][ col ];
		Cell* right = m_grid[ row ][ col + 1 ];
		Cell* left	= m_grid[ row ][ col - 1 ];

		if( up && ( row - 1 ) >= 0 ) 
			m_neighbors[ idx ].push_back( { up, TOP } );
		
		if( right && ( col + 1 ) < api::m_columns )
			m_neighbors[ idx ].push_back( { right, RIGHT } );

		if( down && ( row + 1 ) < api::m_rows ) 
			m_neighbors[ idx ].push_back( { down, BOTTOM } );
		
		if( left && ( col - 1 ) >= 0 )
			m_neighbors[ idx ].push_back( { left, LEFT } );
	}
}

void Maze::ColorNeighbors( ) {

	int index = 1;

	if( m_neighbors[ index ].empty( ) )
		return;

	for( int i = 0; i < m_neighbors[ index ].size( ); i++ ) {
		Cell* neighbor = m_neighbors[ index ].at( i ).neighbor_cell;


		for( auto it : neighbor->m_vertices )
			it.self->setFillColor( sf::Color::Red );
	}
}

// walls overlap so we need to remove both.
void Maze::RemoveWalls( Cell* one, Cell* two ) {

	// figure out which wall to remove based on where the cell is in relation to first cell.
	// if all neighbors exist then they go in the same order as walls.

	for( auto it : m_neighbors[ one->m_index ] ) {

		// if the 2nd cell is indeed one of our neighbors, remove the wall between us.
		if( it.neighbor_cell == two ) {
			if( it.side == RIGHT ) {
				one->RemoveWall( RIGHT );
				it.neighbor_cell->RemoveWall( LEFT );
				break;
			}

			else if( it.side == LEFT ) {
				one->RemoveWall( LEFT );
				it.neighbor_cell->RemoveWall( RIGHT );
				break;
			}

			else if( it.side == TOP ) {
				one->RemoveWall( TOP );
				it.neighbor_cell->RemoveWall( BOTTOM );
				break;
			}

			else if( it.side == BOTTOM ) {
				one->RemoveWall( BOTTOM );
				it.neighbor_cell->RemoveWall( TOP );
				break;
			}
		}	
	}
}

void Maze::ColorVisitedCells( ) {
	for( auto it : m_cells ) {
		if( !it )
			continue;

		if( it->m_visited ) {
			for( auto it : it->m_vertices )
				it.self->setFillColor( sf::Color::Magenta );
		}
	}
}

void Maze::Think(  ) {
	
	if( m_current_cell ) {

		for( auto it : m_neighbors[ m_current_cell->m_index ] ) {
			if( !it.neighbor_cell->m_visited )
				stack.push_back( m_current_cell );
		}

		int num_neighbors = m_neighbors[ m_current_cell->m_index ].size( ) - 1;

		
		Cell* next_cell = m_neighbors[ m_current_cell->m_index ].at( api::random_int( 0, num_neighbors ) ).neighbor_cell;

		if( next_cell && !next_cell->m_visited ) {

			this->RemoveWalls( m_current_cell, next_cell );
			next_cell->m_visited = true;
			m_current_cell = next_cell;
		}
		else if( stack.size( ) > 0 ) {
			m_current_cell = stack.back( );
			stack.pop_back( );
		}

	}
}

void Maze::Run( ) {

	this->Think( );
	this->DrawCells( );
}

void Maze::DrawCells( ) {


	for( int i = 0; i < m_cells.size( ); i++ ) {
		Cell* it = m_cells[ i ];

		if( !it )
			continue;

		it->DrawSelf( );
	}
}

void Maze::Initialize( ) {

	// call functions that need to be only called once.
	this->CreateCells( );
	this->IndexCells( );
	this->FindNeighboringCells( );

	this->m_initial_cell = m_grid[ 0 ][ 0 ];
	m_initial_cell->m_visited = true;
	m_current_cell = m_initial_cell;
}