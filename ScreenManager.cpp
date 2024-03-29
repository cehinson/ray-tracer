#include "ScreenManager.h"

namespace ch
{

ScreenManager::ScreenManager(size_t rows, size_t cols) : nr{rows},
														 nc{cols}
{
	// SETUP SDL
	sdl_check(SDL_Init(SDL_INIT_VIDEO) != -1);
	window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nc, nr, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL), window_deleter{});
	renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(), -1, 0), renderer_deleter{});
	// Draw a black screen to clear the screen
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer.get());
	SDL_RenderPresent(renderer.get());

	screen = SDL_CreateRGBSurface(0, nc, nr, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	texture = std::shared_ptr<SDL_Texture>(SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, nc, nr),texture_deleter{});
}

ScreenManager::~ScreenManager()
{
	SDL_Quit();
}

void ScreenManager::render()
{
	SDL_UpdateTexture(texture.get(), NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer.get());
	SDL_RenderCopy(renderer.get(), texture.get(), NULL, NULL);
	SDL_RenderPresent(renderer.get());
}

void ScreenManager::save()
{
	SDL_SaveBMP(screen, "Output.bmp");
}

void ScreenManager::put_pixels(int row, std::vector<Vec3<>> col)
{
	for (size_t i = 0; i < col.size(); i++)
	{
		put_pixel(i, row, col[i]);
	}
}

void ScreenManager::put_pixel(int x, int y, Vec3<> v)
{
	const auto r = static_cast<int>(255.99f * v.x);
	const auto g = static_cast<int>(255.99f * v.y);
	const auto b = static_cast<int>(255.99f * v.z);
	auto pixel = SDL_MapRGB(screen->format, (Uint8)r, (Uint8)g, (Uint8)b);

	assert(screen->format->BytesPerPixel == 4);
	auto pixel_address = reinterpret_cast<uint32_t *>(screen->pixels) + y * screen->w + x;
	*pixel_address = pixel;
}

} // namespace ch