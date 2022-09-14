#include "maze.h"


Cell::Cell( int x, int y ) {

	sf::RectangleShape* top = new sf::RectangleShape( );

	top->setSize( sf::Vector2f( cell_size, 1.f ) );
	top->setPosition( { static_cast< float >( x ) * cell_size, static_cast< float >( y ) * cell_size } );
	top->setFillColor( sf::Color::White );

	m_vertices.push_back( top );

	sf::RectangleShape* right = new sf::RectangleShape( );

	right->setSize( sf::Vector2f( 1.f, cell_size ) );
	right->setPosition( { (static_cast< float >( x ) * cell_size) + cell_size, static_cast< float >( y ) * cell_size } );
	right->setFillColor( sf::Color::White );

	m_vertices.push_back( right );

	sf::RectangleShape* bottom = new sf::RectangleShape( );

	bottom->setSize( sf::Vector2f( cell_size, 1.f ) );
	bottom->setPosition( { static_cast< float >( x ) * cell_size, (static_cast< float >( y ) * cell_size) + cell_size } );
	bottom->setFillColor( sf::Color::White );

	m_vertices.push_back( bottom );

	sf::RectangleShape* left = new sf::RectangleShape( );

	left->setSize( sf::Vector2f( 1.f, cell_size ) );
	left->setPosition( { static_cast< float >( x ) * cell_size , static_cast< float >( y ) * cell_size } );
	left->setFillColor( sf::Color::White );

	m_vertices.push_back( left );
}

void Cell::RemoveWall( int wall ) {
	if( !this || this->m_vertices.empty( ) )
		return;

	// instead of deleting this vertice, just null the pointer out since we might for whatever reason try do add it back.
	// not to mention how then the walls would shift.
	//this->m_vertices.emplace( this->m_vertices.begin( ) + wall, new sf::RectangleShape( ) );
	this->m_vertices.clear( );
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

		Cell* down = m_grid[ row + 1 ][ col ];
		Cell* up = m_grid[ row - 1 ][ col ];
		Cell* right = m_grid[ row ][ col + 1 ];
		Cell* left = m_grid[ row ][ col - 1 ];

		if( down && ( row + 1 ) < api::m_rows )
			m_neighbors[ idx ].push_back( down );

		if( up && ( row - 1 ) >= 0 )
			m_neighbors[ idx ].push_back( up );

		if( right && ( col + 1 ) < api::m_columns )
			m_neighbors[ idx ].push_back( right );

		if( left && ( col - 1 ) >= 0 )
			m_neighbors[ idx ].push_back( left );
	}
}

void Maze::ColorNeighbors( ) {

	int index = 1;

	if( m_neighbors[ index ].empty( ) )
		return;

	for( int i = 0; i < m_neighbors[ index ].size( ); i++ ) {
		Cell* neighbor = m_neighbors[ index ].at( i );


		for( auto it : neighbor->m_vertices )
			it->setFillColor( sf::Color::Red );
	}
}

void Maze::Run( ) {

	FindNeighboringCells( );
	DrawCells( );
	//ColorNeighbors( );

}

void Maze::DrawCells( ) {

	m_grid[ 1 ][ 4 ]->RemoveWall( 2 );

	for( int i = 0; i < m_cells.size( ); i++ ) {
		Cell* it = m_cells[ i ];

		if( !it )
			continue;

		it->DrawSelf( );
	}

	m_grid[ 5 ][ 0 ]->RemoveWall( 2 );
}