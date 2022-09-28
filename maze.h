#pragma once
#include "include.h"
#include "customrect.h"
constexpr float cell_size = 40.f;
constexpr int max_cells = 400;


enum Sides{
	TOP = 0,
	RIGHT = 1,
	BOTTOM = 2,
	LEFT = 3,
};

struct vertex_t {
	sf::RectangleShape* self;
	bool m_should_draw = true;
};

class Cell;
struct neighbors_t {
	Cell* neighbor_cell;
	size_t side;
};

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
			if( it.self != nullptr && it.m_should_draw )
				DRAW( *it.self );
		}
	}

	void RemoveWall( int wall );

	bool m_visited = false;
	int m_index = 0;
	int m_index_row;
	int m_index_column;

	std::deque< vertex_t > m_vertices;
};

class Maze {
public:

	std::vector<Cell*> m_cells;
	Cell* m_grid[ 10 ][ 10 ];
	Cell* m_current_cell;
	Cell* m_initial_cell;

	//find all neightbors for cell at index.
	std::vector< neighbors_t > m_neighbors[ max_cells ];
	std::vector< Cell* > stack;


	void CreateCells( );
	Cell* GetCell( int i, int j );
	void DrawCells( );
	void Initialize( );
	void IndexCells( );
	void FindNeighboringCells( );

	// debug.
	void ColorNeighbors( );
	void ColorVisitedCells( );

	void Think( );
	void RemoveWalls( Cell * one, Cell * two );
	void Run( );

};

