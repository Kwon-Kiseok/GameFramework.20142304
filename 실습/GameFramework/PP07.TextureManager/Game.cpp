#include "Game.h"

bool Game::init(const char*title, int xpos, int ypos,
	int width, int height, bool fullscreen)
{
	//main.cpp에서 m_bRunning 으로 게임 반복문의 조건을 보고 있음
	//Game.h 에서 m_bRunning 이 false 값으로 초기화 되어있기 때문에 
	//init이 될 때 게임이 돌아간다는 것을 보여주기 위해 true로 할당해줌
	m_bRunning = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow("HOSEO BAR",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640, 480, SDL_WINDOW_SHOWN);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

		}
		//SDL_Surface* pTempSurface = IMG_Load("Assets/animate.png");		
		//SDL_Surface* pTempSurface = IMG_Load("Assets/animate-alpha.png");	//알파
		SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
		//m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
		//SDL_FreeSurface(pTempSurface);

		m_textureManager.load("Assets/animate-alpha.png", "animate", m_pRenderer);
	

		//SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

		//m_sourceRectangle.w = 128;
		//m_sourceRectangle.h = 82;

		//원본 사각형 : m_sourceRectangle    대상 사각형 : m_destinationRectangle
		//m_destinationRectangle.x = m_sourceRectangle.x = 0;
		//m_destinationRectangle.y = m_sourceRectangle.y = 0;
		//m_destinationRectangle.w = m_sourceRectangle.w;
		//m_destinationRectangle.h = m_sourceRectangle.h;

	}
	else
	{
		return 1;
	}
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	//원본 사각형과 대상 사각형의 위치와 크기에 따라 화면에 다르게 나타남
	//SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
	m_textureManager.draw("animate", 0, 0, 128, 82, m_pRenderer);
	m_textureManager.drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	//m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
	//m_destinationRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}