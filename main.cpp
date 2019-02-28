#include <SFML/Graphics.hpp>
#include "header.h"
#include "World.h"
#include "Plane.h"
#include "Vector3.h"
#include "Cube.h"
#include <memory>
#include <string>

#define DEBUG false

enum MODE { CAMERA, CREATION, SELECTION };

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "UMotor");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock deltaClock;

    Vector3 v(0.f, 0.f, 0.f);
    // Create graphics world
    World w;
    // Create camera in position (0, 0, 0) and null rotation
    std::shared_ptr<Entity> cam;
    w.setCamera(cam);
    std::shared_ptr<Plane> plane(new Plane(Vector3(0.f, 0.f, 0.f), 3.0f));

    std::shared_ptr<Cube> skybox(new Cube(0.2, Vector3(0, 0, 0)));
    // Create skybox
    sf::Texture tex;
    tex.setSmooth(true);
    const std::string skyNames[6] = {"Skybox/bluecloud_lf.jpg", 
				     "Skybox/bluecloud_bk.jpg", 
				     "Skybox/bluecloud_rt.jpg",
				     "Skybox/bluecloud_ft.jpg",
				     "Skybox/bluecloud_dn.jpg",
				     "Skybox/bluecloud_up.jpg"};
    for(int i = 0; i < 6; i++)
    {
	    tex.loadFromFile(skyNames[i]);
	    skybox->planes[i]->setTexture(tex);
    }

    std::shared_ptr<Cube> cube(new Cube(0.2, Vector3(0, 0, -2.0)));
    std::shared_ptr<Cube> cube2(new Cube(0.2, Vector3(0, 0, 2.0)));
    std::shared_ptr<Cube> cube3(new Cube(0.2, Vector3(2.0, 0, 0.0)));
    std::shared_ptr<Cube> cube4(new Cube(0.2, Vector3(-2.0, 0, 0.0)));
    w.addEntity(cube);
    //w.addEntity(skybox);
    //w.addEntity(plane);
    w.addEntity(cube2);
    w.addEntity(cube3);
    w.addEntity(cube4);
    int lastX = 0;
    int lastY = 0;
    bool mousePressed = false;

    while (window.isOpen())
    {
	sf::Time dt = deltaClock.restart();
	float deltaTime = dt.asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

	    if (event.type == sf::Event::MouseButtonPressed)
	    {
	    	mousePressed = true;
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }
	    if (event.type == sf::Event::MouseButtonReleased)
	    {
	    	mousePressed = false;
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
		cube->applyRotation();
	    }
	    if (event.type == sf::Event::MouseMoved)
	    {
		cube->isSelected(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            }

	    Vector3 tr(0, 0, 0);
	    float speed = 0.1f * 100.0f;
	    float angleX = 1.0f;
	    float angleY = 1.0f;

	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    {
		tr = tr + Vector3(-speed * deltaTime, 0, 0);
		/*cube->rotate(-angleX, 0);
		cube2->rotate(-angleX, 0);
		cube3->rotate(-angleX, 0);
		cube4->rotate(-angleX, 0);*/
	    }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	    {
		tr = tr + Vector3(speed * deltaTime, 0, 0);
		/*cube->rotate(angleX, 0);
		cube2->rotate(angleX, 0);
		cube3->rotate(angleX, 0);
		cube4->rotate(angleX, 0);*/
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
		tr = tr + Vector3(0, 0, -speed * deltaTime);
		/*cube->rotate(0, angleY);
		cube2->rotate(0, angleY);
		cube3->rotate(0, angleY);
		cube4->rotate(0, angleY);*/
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    {
		tr = tr + Vector3(0, 0, speed * deltaTime);
		/*cube->rotate(0, -angleY);
		cube2->rotate(0, -angleY);
		cube3->rotate(0, -angleY);
		cube4->rotate(0, -angleY);*/
	    }
	
	    if(tr != Vector3(0, 0, 0))
	    {
		cube->translate(tr);
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	    {
		cube->scale(Vector3(1.1f, 1.1f, 1.1f));
		
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	    {
		cube->scale(Vector3(0.9f, 0.9f, 0.9f));
	    }
		
	    if (mousePressed)
	    {

		float _angleY = (lastX - event.mouseMove.x) / 10.0f;
		float _angleX = (lastY - event.mouseMove.y) / 10.0f;

		if(DEBUG)
		{
			std::cout << "angleX : " << angleX << std::endl;
			std::cout << "angleY : " << angleY << std::endl;
		}


		//skybox->rotate(angleX, angleY);
		cube->rotate(_angleX,- _angleY);
		cube2->rotate(_angleX, -_angleY);
		cube3->rotate(_angleX, -_angleY);
		cube4->rotate(_angleX, -_angleY);
		
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }
	    
    	}
	
	//cube->rotate(0, 0);
        window.clear(sf::Color::Black);
        //window.draw(shape);
	w.draw(window);
        window.display();
	
    }
    //delete &w;    

    return 0;
}
