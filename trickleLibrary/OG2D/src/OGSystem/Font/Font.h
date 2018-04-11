#pragma once
#include "OGSystem\_OGsystem.h"
#include "fontstash.h"
#include "glfontstash.h"
class FontImg
{
	GLuint id_;
public:
	FontImg();
	~FontImg();
	void Bind() const;
	void UnBind() const;
};

class Font
{
private:
	/*FT_Library lib;
	FT_Face face;
	FT_GlyphSlot slot;
	FT_Long id_;*/
	Vec2 Size;
	class Context
	{
	public:
		std::shared_ptr<FontImg> tex_;
		Vec2 size;
	};
	Context context_;
	FONScontext* f_context_;
	int DefaulutFontSize = 20;
	int FontNormal = FONS_INVALID;
	static int create(void* userPtr, int width, int height);
	static int resize(void* userPtr, int width, int height);
	static void update(void* userPtr, int* rect, const unsigned char* data);
	static void draw(void* userPtr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts);
public:
	Font();
	Font(std::string fontdatapath_);
	~Font();
	void ResizeFont(const int size_);
	Vec2 drawSize(const std::string& text_);
	void Draw(const std::string& text_, const Vec2& pos_, const Color& color_);
};