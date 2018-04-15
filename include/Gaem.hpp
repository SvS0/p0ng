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

    enum WallType
    {
        TOP,
        LEFT,
        RIGHT,
        BOTTOM
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
        void restartGaem();

    private:
        static const sf::Time TimePerFrame;
 
        sf::RenderWindow mWindow;
        sf::FloatRect mViewBounds;

        bool mIsPlaying;
        bool mIsTouched;

        sf::RectangleShape mP1;
        sf::Vector2f mP1Direction;
        float mP1Vel;

        sf::RectangleShape mP2;
        sf::Vector2f mP2Direction;
        float mP2Vel;

        sf::CircleShape mBall;
        sf::FloatRect mBallBounds; 
        float mBallVel;
        sf::Vector2f mBallDirection;

        PlayerType mLastPlayerCollide;
        std::map <WallType, sf::FloatRect> mWallsMap;
        std::map <PlayerType, sf::FloatRect> mGoalsMap;

        int mScoreP1;
        int mScoreP2;
        
        sf::Text mTextScoreP1;
        sf::Text mTextScoreP2;

        sf::Font mFont;
};

#endif // GAEM_HPP