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
		m_scale = 1.0f;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		DrawSprite(olc::vi2d(0, 0), m_background.get());	
		std::int16_t wheel = GetMouseWheel();
		if(wheel != 0) {
			if (wheel > 0) {
				m_scale += 0.05f;
			}
			else if(m_scale > 0.05f){
				m_scale -= 0.05f;
			}
		}
		std::string statusTxt = "Mouse wheel: " + std::to_string(wheel);
		olc::vi2d mousePos = GetMousePos();
		olc::vf2d pos{
			(float)(mousePos.x - m_atlas->partialSize().x / 2 * m_scale),
			(float)(mousePos.y - m_atlas->partialSize().y / 2 * m_scale)
		};

		DrawStringDecal(olc::vf2d(10.0f, 10.0f), statusTxt);
		m_atlas->RenderSprite(pos, olc::vf2d(m_scale, m_scale), m_frame++, 0);
		if (m_frame >= m_atlas->columns()) {
			m_frame = 0;
		}


		return true;
	}
private:
	std::unique_ptr<codesmith::ImageAtlas> m_atlas;
	std::shared_ptr<olc::Sprite> m_background;
	std::uint16_t m_frame;
	std::float_t m_scale;
};

int main()
{
	PGEApplication demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}
