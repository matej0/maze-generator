#pragma once
#include "include.h"
#include "customrect.h"
constexpr float cell_size = 40.f;
constexpr int max_cells = 400;


class Cell {
public:
	Cell( int x, int y );
	/*Cell( int x, int y ) {
		this->setPosition( { static_cast< float >( x ) * cell_size, static_cast< float >( y ) * cell_size } );
		this->setSize( { cell_size, cell_size } );
		this->setFillColor( sf::Color::Transparent );
		this->setOutlineColor( sf::Color::White );
		this->setOutlineThickness( 1.f );
		
	};*/

	void DrawSelf( ) {
		for( auto it : m_vertices ) {
			if( it != nullptr )
				DRAW( *it );
		}
	}

	void RemoveWall( int wall );

	bool m_visited;
	int m_index = 0;
	int m_index_row;
	int m_index_column;

	std::deque< sf::RectangleShape* > m_vertices;
};

class Maze {
public:

	std::vector<Cell*> m_cells;
	Cell* m_grid[ 20 ][ 20 ];

	//find all neightbors for cell at index.
	std::vector<Cell*> m_neighbors[ max_cells ];

	void CreateCells( );
	Cell* GetCell( int i, int j );
	void DrawCells( );
	void IndexCells( );
	void FindNeighboringCells( );

	// debug.
	void ColorNeighbors( );

	void Run( );

};

