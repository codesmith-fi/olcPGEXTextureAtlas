olcPGEX_AnimatedSprite
This extension is designed for use with the olcPixelGameEngine (https://github.com/OneLoneCoder/olcPixelGameEngine) by Javidx9. It allows you to easily use animated sprites that utilise either single-file spritesheets or multiple image files for each frame.

olcPixelGameEngine is made by Javidx9
TextureAtlas is made by Erno Pakarinen

Usage

    To create a new atlas use something like this:
		std::shared_ptr<olc::Sprite> atlassprite = std::make_shared<olc::Sprite>("Assets\\soniccd.png");
		m_atlas = std::make_unique<olc::TextureAtlas>(atlassprite, 11, 1);

    To render sub sprites from the atlas:
        olc::vf2d position(100.0f, 100.0f);
        olc::vf2d scale(1.0f, 1.0f);
        int x = 0;
        int y = 0; 
        // Draw a sub sprite from row number 'y' and column 'x'
        m_atlas->Draw(position, scale, x, y);


