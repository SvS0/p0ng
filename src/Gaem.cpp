#include <Gaem.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

Gaem::Gaem()
: mWindow(sf::VideoMode(800, 600), "PROTOS", sf::Style::Close)
{
    //enables/disable key press repeat
    mWindow.setKeyRepeatEnabled(false);
}

const sf::Time Gaem::TimePerFrame = sf::seconds(1.f/60.f);

void Gaem::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

        }

        render();
    }
}

void Gaem::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
   
}

void Gaem::update(sf::Time dt) { }

void Gaem::render()
{
    mWindow.clear();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}