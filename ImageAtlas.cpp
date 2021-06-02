#include "ImageAtlas.h"
#include "pge/olcPixelGameEngine.h"

namespace codesmith {

void ImageAtlas::RenderSprite(const olc::vi2d& pos, std::uint16_t x, std::uint16_t y)
{
	olc::vf2d fpos((float)pos.x, (float)pos.y);
	olc::vf2d scale(0.5f, 0.5f);
	if (y < m_rows && x < m_columns) {
		olc::vi2d sourcepos(x*m_partialSize.x, y*m_partialSize.y);
		m_engine->DrawPartialDecal(fpos, m_partialSize, m_atlasDecal.get(), sourcepos, m_partialSize);
	}
}

}

