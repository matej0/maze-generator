#pragma once
#include "include.h"

class SFML_GRAPHICS_API CustomShape : public sf::Drawable, public sf::Transformable
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///
	////////////////////////////////////////////////////////////
	~CustomShape( );

	////////////////////////////////////////////////////////////
	/// \brief Change the source texture of the shape
	///
	/// The \a texture argument refers to a texture that must
	/// exist as long as the shape uses it. Indeed, the shape
	/// doesn't store its own copy of the texture, but rather keeps
	/// a pointer to the one that you passed to this function.
	/// If the source texture is destroyed and the shape tries to
	/// use it, the behavior is undefined.
	/// \a texture can be NULL to disable texturing.
	/// If \a resetRect is true, the TextureRect property of
	/// the shape is automatically adjusted to the size of the new
	/// texture. If it is false, the texture rect is left unchanged.
	///
	/// \param texture   New texture
	/// \param resetRect Should the texture rect be reset to the size of the new texture?
	///
	/// \see getTexture, setTextureRect
	///
	////////////////////////////////////////////////////////////
	void setTexture( const sf::Texture* texture, bool resetRect = false );

	////////////////////////////////////////////////////////////
	/// \brief Set the sub-rectangle of the texture that the shape will display
	///
	/// The texture rect is useful when you don't want to display
	/// the whole texture, but rather a part of it.
	/// By default, the texture rect covers the entire texture.
	///
	/// \param rect Rectangle defining the region of the texture to display
	///
	/// \see getTextureRect, setTexture
	///
	////////////////////////////////////////////////////////////
	void setTextureRect( const sf::IntRect& rect );

	////////////////////////////////////////////////////////////
	/// \brief Set the fill color of the shape
	///
	/// This color is modulated (multiplied) with the shape's
	/// texture if any. It can be used to colorize the shape,
	/// or change its global opacity.
	/// You can use sf::Color::Transparent to make the inside of
	/// the shape transparent, and have the outline alone.
	/// By default, the shape's fill color is opaque white.
	///
	/// \param color New color of the shape
	///
	/// \see getFillColor, setOutlineColor
	///
	////////////////////////////////////////////////////////////
	void setFillColor( const sf::Color& color );

	////////////////////////////////////////////////////////////
	/// \brief Set the outline color of the shape
	///
	/// By default, the shape's outline color is opaque white.
	///
	/// \param color New outline color of the shape
	///
	/// \see getOutlineColor, setFillColor
	///
	////////////////////////////////////////////////////////////
	void setOutlineColor( const sf::Color& color );

	////////////////////////////////////////////////////////////
	/// \brief Set the thickness of the shape's outline
	///
	/// Note that negative values are allowed (so that the outline
	/// expands towards the center of the shape), and using zero
	/// disables the outline.
	/// By default, the outline thickness is 0.
	///
	/// \param thickness New outline thickness
	///
	/// \see getOutlineThickness
	///
	////////////////////////////////////////////////////////////
	void setOutlineThickness( float thickness );

	////////////////////////////////////////////////////////////
	/// \brief Get the source texture of the shape
	///
	/// If the shape has no source texture, a NULL pointer is returned.
	/// The returned pointer is const, which means that you can't
	/// modify the texture when you retrieve it with this function.
	///
	/// \return Pointer to the shape's texture
	///
	/// \see setTexture
	///
	////////////////////////////////////////////////////////////
	const sf::Texture* getTexture( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the sub-rectangle of the texture displayed by the shape
	///
	/// \return Texture rectangle of the shape
	///
	/// \see setTextureRect
	///
	////////////////////////////////////////////////////////////
	const sf::IntRect& getTextureRect( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the fill color of the shape
	///
	/// \return Fill color of the shape
	///
	/// \see setFillColor
	///
	////////////////////////////////////////////////////////////
	const sf::Color& getFillColor( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the outline color of the shape
	///
	/// \return Outline color of the shape
	///
	/// \see setOutlineColor
	///
	////////////////////////////////////////////////////////////
	const sf::Color& getOutlineColor( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the outline thickness of the shape
	///
	/// \return Outline thickness of the shape
	///
	/// \see setOutlineThickness
	///
	////////////////////////////////////////////////////////////
	float getOutlineThickness( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the total number of points of the shape
	///
	/// \return Number of points of the shape
	///
	/// \see getPoint
	///
	////////////////////////////////////////////////////////////
	std::size_t getPointCount( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get a point of the shape
	///
	/// The returned point is in local coordinates, that is,
	/// the shape's transforms (position, rotation, scale) are
	/// not taken into account.
	/// The result is undefined if \a index is out of the valid range.
	///
	/// \param index Index of the point to get, in range [0 .. getPointCount() - 1]
	///
	/// \return index-th point of the shape
	///
	/// \see getPointCount
	///
	////////////////////////////////////////////////////////////
	sf::Vector2f getPoint( std::size_t index ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the local bounding rectangle of the entity
	///
	/// The returned rectangle is in local coordinates, which means
	/// that it ignores the transformations (translation, rotation,
	/// scale, ...) that are applied to the entity.
	/// In other words, this function returns the bounds of the
	/// entity in the entity's coordinate system.
	///
	/// \return Local bounding rectangle of the entity
	///
	////////////////////////////////////////////////////////////
	sf::FloatRect getLocalBounds( ) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the global (non-minimal) bounding rectangle of the entity
	///
	/// The returned rectangle is in global coordinates, which means
	/// that it takes into account the transformations (translation,
	/// rotation, scale, ...) that are applied to the entity.
	/// In other words, this function returns the bounds of the
	/// shape in the global 2D world's coordinate system.
	///
	/// This function does not necessarily return the \a minimal
	/// bounding rectangle. It merely ensures that the returned
	/// rectangle covers all the vertices (but possibly more).
	/// This allows for a fast approximation of the bounds as a
	/// first check; you may want to use more precise checks
	/// on top of that.
	///
	/// \return Global bounding rectangle of the entity
	///
	////////////////////////////////////////////////////////////
	sf::FloatRect getGlobalBounds( ) const;

	sf::VertexArray getOutlineVertices( ) const;

	void setOutlineVertices( sf::VertexArray & vertices );

	////////////////////////////////////////////////////////////
	/// \brief Set the size of the rectangle
	///
	/// \param size New size of the rectangle
	///
	/// \see getSize
	///
	////////////////////////////////////////////////////////////
	void setSize( const sf::Vector2f& size );

	////////////////////////////////////////////////////////////
	/// \brief Get the size of the rectangle
	///
	/// \return Size of the rectangle
	///
	/// \see setSize
	///
	////////////////////////////////////////////////////////////
	const sf::Vector2f& getSize( ) const;

protected:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	////////////////////////////////////////////////////////////
	CustomShape( );

	////////////////////////////////////////////////////////////
	/// \brief Recompute the internal geometry of the shape
	///
	/// This function must be called by the derived class everytime
	/// the shape's points change (i.e. the result of either
	/// getPointCount or getPoint is different).
	///
	////////////////////////////////////////////////////////////
	void update( );

private:

	////////////////////////////////////////////////////////////
	/// \brief Draw the shape to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

	////////////////////////////////////////////////////////////
	/// \brief Update the fill vertices' color
	///
	////////////////////////////////////////////////////////////
	void updateFillColors( );

	////////////////////////////////////////////////////////////
	/// \brief Update the fill vertices' texture coordinates
	///
	////////////////////////////////////////////////////////////
	void updateTexCoords( );

	////////////////////////////////////////////////////////////
	/// \brief Update the outline vertices' position
	///
	////////////////////////////////////////////////////////////
	void updateOutline( );

	////////////////////////////////////////////////////////////
	/// \brief Update the outline vertices' color
	///
	////////////////////////////////////////////////////////////
	void updateOutlineColors( );


private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	const sf::Texture* m_texture;          ///< Texture of the shape
	sf::IntRect        m_textureRect;      ///< Rectangle defining the area of the source texture to display
	sf::Color          m_fillColor;        ///< Fill color
	sf::Color          m_outlineColor;     ///< Outline color
	float			   m_outlineThickness; ///< Thickness of the shape's outline
	sf::VertexArray    m_vertices;         ///< Vertex array containing the fill geometry
	sf::VertexArray    m_outlineVertices;  ///< Vertex array containing the outline geometry
	sf::FloatRect      m_insideBounds;     ///< Bounding rectangle of the inside (fill)
	sf::FloatRect      m_bounds;           ///< Bounding rectangle of the whole shape (outline + fill)
	sf::Vector2f	   m_size; ///< Size of the rectangle

};

