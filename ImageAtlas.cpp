#include "ImageAtlas.h"
#include "pge/olcPixelGameEngine.h"

namespace codesmith {

void ImageAtlas::RenderSprite(const olc::vi2d& pos, const olc::vf2d& scale, 
	std::uint16_t x, std::uint16_t y)
{
	olc::vf2d fpos((float)pos.x, (float)pos.y);
	if (y < m_rows && x < m_columns) {
		olc::vf2d size(m_partialSize.x * scale.x, m_partialSize.y * scale.y);
		olc::vi2d sourcepos(x*m_partialSize.x, y*m_partialSize.y);
		m_engine->DrawPartialDecal(fpos, size, m_atlasDecal.get(), sourcepos, m_partialSize);
	}
}

}

