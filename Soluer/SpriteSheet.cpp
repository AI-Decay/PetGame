#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, std::shared_ptr<Graphics> graphics)
	: gfx(graphics), bmp(NULL)
{
	IWICImagingFactory* wicFactory = NULL;
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory, reinterpret_cast<LPVOID*>(&wicFactory));
		
	IWICBitmapDecoder* wicDecoder = NULL;
	wicFactory->CreateDecoderFromFilename(filename, NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, &wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter* wicConverter = NULL;
	wicFactory->CreateFormatConverter(&wicConverter);

	wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPBGRA, 
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);

	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	spriteHeight = bmp->GetSize().height;
	spriteWidth = bmp->GetSize().width;
	spriteAccross = 1;
}


SpriteSheet::SpriteSheet(const wchar_t* filename, std::shared_ptr<Graphics> graphics, int spriteWidth, int spriteHeight)
	:SpriteSheet(filename, graphics)
{
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spriteAccross = bmp->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet() 
{
	//if (bmp) bmp->Release();
}

void SpriteSheet::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(bmp, D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		0.2f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
}

void SpriteSheet::Draw(int index, int x, int y)
{
	D2D_RECT_F src = D2D1::RectF(
		static_cast<float>((index % spriteAccross) * spriteWidth),
		static_cast<float>((index / spriteAccross) * spriteHeight),
		static_cast<float>((index % spriteAccross) * spriteWidth + spriteWidth),
		static_cast<float>((index / spriteAccross) * spriteHeight + spriteHeight));

	D2D_RECT_F dest = D2D1::RectF(x, y, x + spriteWidth, y + spriteHeight);



	gfx->GetRenderTarget()->DrawBitmap(bmp, dest, 1.0f, 
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
}