#include "Renderer.h"
#include "Framebuffer.h"
#include "2DRenderer/Image.h"
#include "2DRenderer/PostProcess.h"

#include <iostream>
#include <SDL.h>

int main(int, char**){
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer.get()->width, renderer.get()->height);
	
	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({0,0,0,0});

        //for (int i = 0; i < 100; i++)
        //{
        //    framebuffer->DrawPoint(rand() % framebuffer->width, rand() % framebuffer->height, { 0, 255, 0, 0 });
        //}
        for (int i = 0; i < 50; i++)
        {
            framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 100, 100, { ((uint8_t)((rand() % 2) * 255)), ((uint8_t)((rand() % 2) * 255)), ((uint8_t)((rand() % 2) * 255)), ((uint8_t)((rand() % 2) * 128)) });
        }
        //for (int i = 0; i < 20; i++)
        //{
        //    framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { ((uint8_t)((rand() % 2) * 255), 255, 255, 0 });
        //}


        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawQuadraticCurve(
        //        rand() % framebuffer->width, rand() % framebuffer->height,
        //        rand() % framebuffer->width, rand() % framebuffer->height,
        //        rand() % framebuffer->width, rand() % framebuffer->height, 30, { 255, 255, 0, 255 });
        //}
        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawCubicCurve(
        //        rand() % framebuffer->width, rand() % framebuffer->height,
        //        rand() % framebuffer->width, rand() % framebuffer->height,
        //        rand() % framebuffer->width, rand() % framebuffer->height,
        //        rand() % framebuffer->width, rand() % framebuffer->height,
        //        30, { 0, 255, 255, 255 });
        //}

        std::unique_ptr<Image> image = std::make_unique<Image>();
        image->Load("../resources/flower.bmp", 200);
        image->Flip();

        //Draw the image
        framebuffer->DrawImage(300, 50, image.get());

        std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
        PostProcess::BoxBlur(image1->colorBuffer);
        framebuffer->DrawImage(0, 300, image1.get());

        std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
        PostProcess::GuassianBlur(image2->colorBuffer);
        framebuffer->DrawImage(200, 300, image2.get());

        std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
        PostProcess::Sharpen(image3->colorBuffer);
        framebuffer->DrawImage(400, 300, image3.get());

        std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
        PostProcess::Monochrome(image4->colorBuffer);
        PostProcess::Edge(image4->colorBuffer, 0);
        framebuffer->DrawImage(600, 300, image4.get());

        ////Not what we are supposed to do / No Monochrome
        //std::unique_ptr<Image> image5 = std::make_unique<Image>(*image.get());
        //PostProcess::Edge(image5->colorBuffer, 0);
        //framebuffer->DrawImage(600, 50, image5.get());



        //PostProcess::Invert(framebuffer->colorBuffer);
        //PostProcess::Monochrome(framebuffer->colorBuffer);
        //PostProcess::Noise(framebuffer->colorBuffer, 100);
        //PostProcess::Brightness(framebuffer->colorBuffer, -100);
        //PostProcess::ColorBalance(framebuffer->colorBuffer, 100, 0, 0);
        //PostProcess::Threshold(framebuffer->colorBuffer, 200);

       /* for (int i = 0; i < 20; i++)
        {
            framebuffer->DrawCircle(rand() % renderer->width, rand() % renderer->height, 30, { 0, 255, 0, 0 });
        }*/

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());

		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
