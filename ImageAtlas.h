#ifndef __TEXTUREATLAS_H_DEFINED__
#define __TEXTUREATLAS_H_DEFINED__

#include "pge/olcPixelGameEngine.h"
#include <memory>

namespace codesmith
{

class TextureAtlas : public olc::PGEX
{
public:
	TextureAtlas(std::shared_ptr<olc::Sprite> atlasSprite, std::uint16_t cols, std::uint16_t rows) :
		m_engine(nullptr), m_atlas(atlasSprite), m_columns(cols), m_rows(rows)
	{ 
		m_atlasDecal = std::make_unique<olc::Decal>(m_atlas.get());		
		m_partialSize = olc::vi2d(atlasSprite->width / cols, atlasSprite->height / rows);
		m_spriteCount = rows * cols;
	};

	virtual ~TextureAtlas() {};

	std::uint16_t rows() const { return m_rows; }
	std::uint16_t columns() const { return m_columns; }
	std::uint16_t sprites() const { return m_spriteCount; }
	olc::vi2d partialSize() const { return m_partialSize; }

	void Draw(const olc::vi2d& pos, const olc::vf2d& scale,
		std::uint16_t x, std::uint16_t y)
	{
		olc::vf2d fpos((float)pos.x, (float)pos.y);
		if (y < m_rows && x < m_columns) {
			olc::vf2d size(m_partialSize.x * scale.x, m_partialSize.y * scale.y);
			olc::vi2d sourcepos(x * m_partialSize.x, y * m_partialSize.y);
			pge->DrawPartialDecal(fpos, size, m_atlasDecal.get(), sourcepos, m_partialSize);
		}
	}

private: // Hidden
	TextureAtlas() : m_engine(nullptr), m_columns(0), m_rows(0), m_spriteCount(0) {};
private:
	olc::PixelGameEngine* m_engine;
	std::shared_ptr<olc::Sprite> m_atlas;
	std::unique_ptr<olc::Decal> m_atlasDecal;
	olc::vi2d m_partialSize;
	std::uint16_t m_columns;
	std::uint16_t m_rows;
	std::uint16_t m_spriteCount;
};

} // namespace codesmith

#endif // __TEXTUREATLAS_H_DEFINED__