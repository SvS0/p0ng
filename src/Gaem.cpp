#include <Gaem.hpp>

#include <Utility.hpp>

#include <cstdlib>
#include <ctime>

Gaem::Gaem()
: mWindow(sf::VideoMode(800, 600), "P0NG", sf::Style::Close)
, mViewBounds(sf::Vector2i(0,0), sf::Vector2i(800, 600))
, mGoalsMap()
{
    //enables/disable key press repeat
    mWindow.setKeyRepeatEnabled(false);

    init();

    //Player && Goals map
    mGoalsMap.insert(std::make_pair(PlayerType::P1, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(0, 600))));
    mGoalsMap.insert(std::make_pair(PlayerType::P2, sf::IntRect(sf::Vector2i(800, 0), sf::Vector2i(800, 600))));

    srand(time(NULL));
    startGaem(static_cast<PlayerType>(rand() % PlayerType::size));
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

void Gaem::init()
{
    mP1 = sf::RectangleShape();
    mP1.setSize(sf::Vector2f(25.0f, 100.0f));
    mP1.setPosition(sf::Vector2f(100.0f, 250.0f));
    mP1.setOutlineThickness(5.0f);
    mP1.setOutlineColor(sf::Color::Cyan);
    mP1.setFillColor(sf::Color::Black);

    mScoreP1 = 0;
    
    mP2 = sf::RectangleShape();
    mP2.setSize(sf::Vector2f(25.0f, 100.0f));
    mP2.setPosition(sf::Vector2f(675.0f, 250.0f));
    mP2.setOutlineThickness(5.0f);
    mP2.setOutlineColor(sf::Color::Magenta);
    mP2.setFillColor(sf::Color::Black);
    mScoreP2 = 0;

    mBall = sf::CircleShape();
    mBall.setPosition(sf::Vector2f(400.0f,300.0f));
    mBall.setRadius(5.0f);
    mBall.setOutlineThickness(2.5f);
    mBall.setOutlineColor(sf::Color::Yellow);
    mBall.setFillColor(sf::Color::Black);
    mBallVel = 100.0f;
}

void Gaem::startGaem(PlayerType player)
{
    mBall.setPosition(400.0f, 300.0f);

    auto it = mGoalsMap.find(player);
    sf::IntRect playerGoal = it->second;
    
    sf::Vector2f rangeVector = sf::Vector2f(playerGoal.top, playerGoal.height) - sf::Vector2f(playerGoal.top, playerGoal.left); 
    float rangeAngle = toDegree((pendant(rangeVector)));

    srand(time(NULL));
    float randomDistance = rand() % (int) length(rangeVector);

    sf::Vector2f targetVector = directionVector(rangeAngle) * randomDistance;

    sf::Vector2f ballVector = targetVector - mBall.getPosition();
        
    mBallAngle = toDegree((pendant(ballVector)));
}

void Gaem::update(sf::Time dt) 
{  
    mBall.setPosition(mBall.getPosition() + (directionVector(mBallAngle) * mBallVel * dt.asSeconds()));
}

void Gaem::render()
{
    mWindow.clear();

    mWindow.draw(mP1);
    mWindow.draw(mP2);
    mWindow.draw(mBall);

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}