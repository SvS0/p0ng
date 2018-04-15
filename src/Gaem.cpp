#include <Gaem.hpp>

#include <Utility.hpp>

#include <cstdlib>
#include <time.h>
#include <string>

Gaem::Gaem()
: mWindow(sf::VideoMode(800, 600), "P0NG", sf::Style::Close)
, mViewBounds(sf::Vector2f(0.0f,0.0f), sf::Vector2f(800.0f, 600.0f))
, mWallsMap()
, mGoalsMap()
, mTextScoreP1()
, mTextScoreP2()
, mFont()
{
    //enables/disable key press repeat
    mWindow.setKeyRepeatEnabled(false);

    init();

    //Walls Map settings
    mWallsMap.insert(std::make_pair(WallType::TOP, sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 1.0f))));
    mWallsMap.insert(std::make_pair(WallType::LEFT, sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 600.0f))));
    mWallsMap.insert(std::make_pair(WallType::RIGHT, sf::FloatRect(sf::Vector2f(800.0f, 0.0f), sf::Vector2f(1.0f, 600.0f))));
    mWallsMap.insert(std::make_pair(WallType::BOTTOM, sf::FloatRect(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(800.0f, 1.0f))));

    //Goals Map settings
    mGoalsMap.insert(std::make_pair(PlayerType::P1, sf::FloatRect(sf::Vector2f(800.0f, 0.0f), sf::Vector2f(1.0f, 600.0f))));
    mGoalsMap.insert(std::make_pair(PlayerType::P2, sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 600.0f))));

    mLastPlayerCollide = PlayerType::NONE;

    mFont.loadFromFile("resources/8bitOperatorPlus8-Bold.ttf");

    mScoreP1 = 0;
    mScoreP2 = 0;

    mIsTouched = false;

    startGaem();
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
    mP1Vel = 100.0f;
    
    mP2 = sf::RectangleShape();
    mP2.setSize(sf::Vector2f(25.0f, 100.0f));
    mP2.setPosition(sf::Vector2f(675.0f, 250.0f));
    mP2.setOutlineThickness(5.0f);
    mP2.setOutlineColor(sf::Color::Magenta);
    mP2.setFillColor(sf::Color::Black);
    mP2Vel = 100.0f;

    mBall = sf::CircleShape();
    mBall.setPosition(sf::Vector2f(400.0f,300.0f));
    mBall.setRadius(5.0f);
    mBall.setOutlineThickness(2.5f);
    mBall.setOutlineColor(sf::Color::Yellow);
    mBall.setFillColor(sf::Color::Black);
    mBallVel = 200.0f;

    mTextScoreP1.setPosition(200,50);
    mTextScoreP1.setFont(mFont);

    mTextScoreP2.setPosition(250, 50);
    mTextScoreP2.setFont(mFont);

}

void Gaem::startGaem()
{
    srand(time(NULL));

    //Choosing random player
    if(mLastPlayerCollide == PlayerType::NONE || !mIsTouched)
    {
        int random = (rand() % 2) + 1;
        mLastPlayerCollide = static_cast<PlayerType>(random);
    }
    mIsTouched = false;
         
    //Choosing random point between player's goal bounds
    sf::Vector2f goalVector = sf::Vector2f(mGoalsMap[mLastPlayerCollide].width, mGoalsMap[mLastPlayerCollide].height);
    int goalLength = length(goalVector);

    sf::Vector2f target = sf::Vector2f(mGoalsMap[mLastPlayerCollide].left, rand() % (int) goalLength);

    //Setting ball direction
    mBallDirection = unitVector(target - mBall.getPosition());

    mIsPlaying = true;
}

void Gaem::update(sf::Time dt) 
{  
    //Player movement management
    if  (!mP1.getGlobalBounds().intersects(mWallsMap[WallType::TOP]) && 
            sf::Keyboard::isKeyPressed(sf::Keyboard::W))  
        mP1.setPosition(sf::Vector2f(mP1.getPosition().x, mP1.getPosition().y - (mP1Vel * dt.asSeconds())));

    if  (!mP1.getGlobalBounds().intersects(mWallsMap[WallType::BOTTOM]) && 
            sf::Keyboard::isKeyPressed(sf::Keyboard::S))  
        mP1.setPosition(sf::Vector2f(mP1.getPosition().x, mP1.getPosition().y + (mP1Vel * dt.asSeconds())));

    if  (!mP2.getGlobalBounds().intersects(mWallsMap[WallType::TOP]) && 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  
        mP2.setPosition(sf::Vector2f(mP2.getPosition().x, mP2.getPosition().y - (mP2Vel * dt.asSeconds())));

    if  (!mP2.getGlobalBounds().intersects(mWallsMap[WallType::BOTTOM]) && 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  
        mP2.setPosition(sf::Vector2f(mP2.getPosition().x, mP2.getPosition().y + (mP2Vel * dt.asSeconds())));

    //Update score
    for(std::map<WallType, sf::FloatRect>::iterator it = mWallsMap.begin(); it != mWallsMap.end(); ++it)
    {
        sf::FloatRect wallBounds = it->second;
        if (wallBounds.intersects(mBall.getGlobalBounds()))
        {
            WallType wall = it->first;
            switch (wall)
            {
                case WallType::TOP :
                    mBallDirection.y *= -1.0f;
                    break;

                case WallType::LEFT : 
                    mScoreP2++;
                    mIsPlaying = false;
                    break;

                case WallType::RIGHT :
                    mScoreP1++;
                    mIsPlaying = false;
                    break;

                case WallType::BOTTOM :
                    mBallDirection.y *= -1.0f;
                    break;

                default :
                    break;
            }
        }
    }

    //naive player's collission
    if (mP1.getGlobalBounds().intersects(mBall.getGlobalBounds()) ||
        mP2.getGlobalBounds().intersects(mBall.getGlobalBounds()))
            mBallDirection.x *= -1.0f;


    //Update textScore
    mTextScoreP1.setString(std::to_string(mScoreP1));
    mTextScoreP2.setString(std::to_string(mScoreP2));

    //Update ball's position
    mBall.setPosition(mBall.getPosition() + (mBallDirection * mBallVel * dt.asSeconds()));

    if (!mIsPlaying)
        restartGaem();
}

void Gaem::render()
{
    mWindow.clear();

    mWindow.draw(mP1);
    mWindow.draw(mP2);
    mWindow.draw(mBall);
    mWindow.draw(mTextScoreP1);
    mWindow.draw(mTextScoreP2);

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Gaem::restartGaem()
{
    init();
    startGaem();
}