#include <iostream>

#define OLC_PGE_APPLICATION
#include "pge/olcPixelGameEngine.h"
#include <memory>
#include "ImageAtlas.h"
#include "DebugLogger.h"

// Override base class with your custom functionality
class PGEApplication: public olc::PixelGameEngine
{
public:
	PGEApplication()
	{
		// Name your application
		sAppName = "PGEApplication";
	}

public:
	bool OnUserCreate() override
	{
		m_background = std::make_shared<olc::Sprite>("Assets\\desert.png");

		std::shared_ptr<olc::Sprite> atlassprite = std::make_shared<olc::Sprite>("Assets\\soniccd.png");
		m_atlas = std::make_unique<codesmith::ImageAtlas>(atlassprite, 11, 1);
		m_atlas->setEngine(this);
		m_frame = 0;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		DrawSprite(olc::vi2d(0, 0), m_background.get());	

		m_atlas->RenderSprite(GetMousePos(), m_frame++, 0);
		if (m_frame >= m_atlas->columns()) {
			m_frame = 0;
		}

		return true;
	}
private:
	std::unique_ptr<codesmith::ImageAtlas> m_atlas;
	std::shared_ptr<olc::Sprite> m_background;
	std::uint16_t m_frame;
};

int main()
{
	PGEApplication demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}
