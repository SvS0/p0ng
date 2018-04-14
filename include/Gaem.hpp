#ifndef GAEM_HPP
#define GAEM_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <map>


class Gaem
{
    public:

    enum PlayerType
    {
        NONE,
        P1,
        P2,
        SIZE
    };

    public:
        Gaem();
        void run();

    private:
        void processInput();
        void update(sf::Time dt);
        void render();

        void init();
        void startGaem();

    private:
        static const sf::Time TimePerFrame;
 
        sf::RenderWindow mWindow;
        sf::FloatRect mViewBounds;

        sf::RectangleShape mP1;
        sf::RectangleShape mP2;

        sf::CircleShape mBall;
        sf::FloatRect mBallBounds; 
        float mBallVel;
        sf::Vector2f mBallDirection;

        PlayerType mLastPlayerCollide;
        std::map <PlayerType, sf::FloatRect> mGoalsMap;

        std::map <PlayerType, int> mScoreMap;
        
        sf::Text mTextScoreP1;
        sf::Text mTextScoreP2;

        sf::Font mFont;
};

#endif // GAEM_HPP