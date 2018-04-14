#include <Gaem.hpp>

#include <Utility.hpp>

#include <cstdlib>
#include <time.h>

Gaem::Gaem()
: mWindow(sf::VideoMode(800, 600), "P0NG", sf::Style::Close)
, mViewBounds(sf::Vector2f(0.0f,0.0f), sf::Vector2f(800.0f, 600.0f))
, mGoalsMap()
, mScoreMap()
, mTextScoreP1()
, mTextScoreP2()
, mFont()
{
    //enables/disable key press repeat
    mWindow.setKeyRepeatEnabled(false);

    init();

    //Player && Goals map
    mGoalsMap.insert(std::make_pair(PlayerType::P1, sf::FloatRect(sf::Vector2f(800.0f, 0.0f), sf::Vector2f(0.0f, 600.0f))));
    mGoalsMap.insert(std::make_pair(PlayerType::P2, sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 600.0f))));

    //Player Score map
    mScoreMap.insert(std::make_pair(PlayerType::P1, 0));
    mScoreMap.insert(std::make_pair(PlayerType::P2, 0));

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
    
    mP2 = sf::RectangleShape();
    mP2.setSize(sf::Vector2f(25.0f, 100.0f));
    mP2.setPosition(sf::Vector2f(675.0f, 250.0f));
    mP2.setOutlineThickness(5.0f);
    mP2.setOutlineColor(sf::Color::Magenta);
    mP2.setFillColor(sf::Color::Black);

    mBall = sf::CircleShape();
    mBall.setPosition(sf::Vector2f(400.0f,300.0f));
    mBall.setRadius(5.0f);
    mBall.setOutlineThickness(2.5f);
    mBall.setOutlineColor(sf::Color::Yellow);
    mBall.setFillColor(sf::Color::Black);
    mBallVel = 200.0f;

    mFont.loadFromFile("resources/8bitOperatorPlus8-Bold.ttf");

    mTextScoreP1.setPosition(200,50);
    mTextScoreP1.setFont(mFont);
    //mTextScoreP1.setString(mScoreMap.find[PlayerType::P1]);

    mTextScoreP2.setPosition(250, 50);
    mTextScoreP2.setFont(mFont);
    //mTextScoreP2.setString(mScoreMap.find[PlayerType::P2]);

}

void Gaem::startGaem()
{
    time_t t;
    srand((unsigned) time(&t));

    //Choosing random player
    if(mLastPlayerCollide == PlayerType::NONE)
    {
        int random = (rand() % 2) + 1;
        mLastPlayerCollide = static_cast<PlayerType>(random);
    }
        
    //Choosing random point between player's goal bounds
    sf::Vector2f goalVector = sf::Vector2f(mGoalsMap[mLastPlayerCollide].width, mGoalsMap[mLastPlayerCollide].height);
    int goalLength = length(goalVector);

    sf::Vector2f mTarget = sf::Vector2f(mGoalsMap[mLastPlayerCollide].left, rand() % (int) goalLength);

    //Setting ball direction
    mBallDirection = unitVector(sf::Vector2f(mTarget - mBall.getPosition()));
}

void Gaem::update(sf::Time dt) 
{  
    //Update score
    for(std::map<PlayerType, sf::FloatRect>::iterator it = mGoalsMap.begin(); it != mGoalsMap.end(); ++it)
    {
        if (mBall.getGlobalBounds().intersects(it->second))
        {
            // int score = mScoreMap.find[it->first];
            // score++;
            // mScoreMap.find[it->first] = score;

        }
    }

    //Update ball's position
    mBall.setPosition(mBall.getPosition() + (mBallDirection * mBallVel * dt.asSeconds()));
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