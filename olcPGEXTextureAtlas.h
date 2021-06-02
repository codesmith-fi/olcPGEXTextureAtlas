/*
	olcPGEX_AnimatedSprite.h
	+-------------------------------------------------------------+
	|         OneLoneCoder Pixel Game Engine Extension            |
	|                TextureAtlas - v0.5.0			              |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	This is an extension to Pixel Game Engine and aims to implement
	a simple texture atlas (or sprite sheet). Texture atlas is basically
	one big sprite having multiple sub images. These sub images can 
	be drawn separately to form textures or animated sprites.
	This class does not animate anything by itself, you must ask the
	Draw() call to draw sub frames separately.

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2021 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions or derivations of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce the above
	copyright notice. This list of conditions and the following	disclaimer must be
	reproduced in the documentation and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors may
	be used to endorse or promote products derived from this software without specific
	prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.

	Links
	~~~~~
	Homepage:	https://github.com/codesmith-fi
	Mail:		codesmith.fi@gmail.com

	Author
	~~~~~~
	Erno Pakarinen (aka xanaki#9472 in discord, aka codesmith-fi)

*/

#ifndef __TEXTUREATLAS_H_DEFINED__
#define __TEXTUREATLAS_H_DEFINED__

#include <memory>

namespace olc
{

class TextureAtlas : public olc::PGEX
{
public:
	TextureAtlas(std::shared_ptr<olc::Sprite> atlasSprite, std::uint16_t cols, std::uint16_t rows) :
		m_atlas(atlasSprite), m_columns(cols), m_rows(rows)
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
	TextureAtlas();
private:
	std::shared_ptr<olc::Sprite> m_atlas;
	std::unique_ptr<olc::Decal> m_atlasDecal;
	olc::vi2d m_partialSize;
	std::uint16_t m_columns;
	std::uint16_t m_rows;
	std::uint16_t m_spriteCount;
};

} // namespace olc

#endif // __TEXTUREATLAS_H_DEFINED__