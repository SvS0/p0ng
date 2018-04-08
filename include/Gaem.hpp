#ifndef GAEM_HPP
#define GAEM_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <map>


class Gaem
{
    public:

    enum PlayerType
    {
        P1,
        P2,
        size
    };

    public:
        Gaem();
        void run();

    private:
        void processInput();
        void update(sf::Time dt);
        void render();

        void init();
        void startGaem(PlayerType player);

    private:
        static const sf::Time TimePerFrame;
 
        sf::RenderWindow mWindow;
        sf::IntRect mViewBounds;

        sf::RectangleShape mP1;
        int mScoreP1;
        
        sf::RectangleShape mP2;
        int mScoreP2;

        sf::CircleShape mBall;
        float mBallVel;
        float mBallAngle;

        std::map <PlayerType, sf::IntRect> mGoalsMap;

};

#endif // GAEM_HPP