//実装を拡張する
#define FONTSTASH_IMPLEMENTATION
#include "Font.h"
FontImg::FontImg()
{
	glGenTextures(1, &this->id_);
}
FontImg::~FontImg()
{
	glDeleteTextures(1, &this->id_);
}
void FontImg::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id_);
}
void FontImg::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
//-------------------------------------------
//@:Fontclass
//-------------------------------------------
int Font::create(void* userPtr, int width, int height)
{
	Context* context_ = (Context*)userPtr;
	context_->tex_ = std::make_shared<FontImg>();
	context_->size.x = width;
	context_->size.y = height;
	context_->tex_->Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, context_->size.x, context_->size.y, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return 1;
}
int Font::resize(void* userPtr, int width, int height)
{
	return create(userPtr, width, height);
}
void Font::update(void* userPtr, int* rect, const unsigned char* data)
{
	Context* context_ = (Context*)userPtr;
	if (!context_->tex_) { return; }
	int w = rect[2] - rect[0];
	int h = rect[3] - rect[1];
	context_->tex_->Bind();
	glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, context_->size.x);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect[0]);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, rect[1]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1], w, h, GL_ALPHA, GL_UNSIGNED_BYTE, data);
	glPopClientAttrib();
}
void Font::draw(void* userPtr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
	Context* context_ = (Context*)userPtr;
	std::cout << "draw" << std::endl;
	if (!context_->tex_) { return; }
	context_->tex_->Bind();
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(float) * 2, verts);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 2, tcoords);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(unsigned int), colors);
	glDrawArrays(GL_TRIANGLES, 0, nverts);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
Font::Font()
{
	//this->f_context_ = glfonsCreate(960, 540, FONS_ZERO_TOPLEFT);
	//if (this->f_context_ == NULL)
	//{
	//	std::cout << "FontError" << std::endl;
	//	return;
	//}
	//this->FontNormal = fonsAddFont(this->f_context_, "sans", "./data/font/msgothic.ttc");
	//if (this->FontNormal == FONS_INVALID)
	//{
	//	std::cout << "FontDataReadError" << std::endl;
	//	return;
	//}
	FONSparams params;
	memset(&params, 0, sizeof(params));
	params.width = 1024;
	params.height = 1024;
	params.flags = (unsigned char)FONS_ZERO_BOTTOMLEFT;
	params.renderCreate = Font::create;
	params.renderResize = Font::resize;
	params.renderUpdate = Font::update;
	params.renderDraw = Font::draw;
	params.renderDelete = nullptr;
	params.userPtr = &this->context_;
	this->f_context_ = fonsCreateInternal(&params);
	fonsClearState(this->f_context_);
	int handle = fonsAddFont(this->f_context_, "font", "msgothic.ttc");
	fonsSetFont(this->f_context_, handle);
	fonsSetSize(this->f_context_, this->DefaulutFontSize);
	// TIPS:下揃えにしておくと、下にはみ出す部分も正しく扱える
	fonsSetAlign(this->f_context_, FONS_ALIGN_BOTTOM);
}
Font::Font(std::string fontdatapath_)
{
	FONSparams params;

	memset(&params, 0, sizeof(params));
	params.width = 1024;
	params.height = 1024;
	params.flags = (unsigned char)FONS_ZERO_BOTTOMLEFT;

	params.renderCreate = Font::create;
	params.renderResize = Font::resize;
	params.renderUpdate = Font::update;
	params.renderDraw = Font::draw;
	params.renderDelete = nullptr;

	params.userPtr = &this->context_;

	this->f_context_ = fonsCreateInternal(&params);

	fonsClearState(this->f_context_);
	int handle = fonsAddFont(this->f_context_, "font", fontdatapath_.c_str());
	fonsSetFont(this->f_context_, handle);
	fonsSetSize(this->f_context_, this->DefaulutFontSize);
	// TIPS:下揃えにしておくと、下にはみ出す部分も正しく扱える
	fonsSetAlign(this->f_context_, FONS_ALIGN_BOTTOM);
}
void Font::ResizeFont(const int size_)
{
	fonsSetSize(this->f_context_, size_);
}
Vec2 Font::drawSize(const std::string& text_)
{
	float b[4];
	fonsTextBounds(this->f_context_, 0, 0, text_.c_str(), nullptr, b);
	return Vec2{ b[2],b[3] };
}
void Font::Draw(const std::string& text_, const Vec2& pos_, const Color& color_)
{
	fonsSetColor(this->f_context_, color_.Getcolor());
	fonsDrawText(this->f_context_, pos_.x, pos_.y, text_.c_str(), nullptr);
}
Font::~Font()
{
	//	glfonsDelete(this->f_context_);
}