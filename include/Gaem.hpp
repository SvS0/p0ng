#ifndef GAEM_HPP
#define GAEM_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>


class Gaem
{
    public:
        Gaem();
        void run();

    private:
        void processInput();
        void update(sf::Time dt);
        void render();

    private:
        static const sf::Time TimePerFrame;

        sf::RenderWindow mWindow;

};

#endif // GAEM_HPP