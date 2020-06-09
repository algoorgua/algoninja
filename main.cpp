#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

const long long DIM = 33;
long double x,y,dy,n;
long long life[DIM]; //житті вірусів
long double velo[DIM]; //швидкості вірусів


int main()
{
    srand(time(0)); //ініціалізуємо генератор випадкових чисел

    //Створюємо вікно розміром 768 (ширина) x 411 (висота)
    sf::RenderWindow window(sf::VideoMode(768, 411), "Algo Ninja 1.0");
    window.setFramerateLimit(60); //Встановлюємо частоту 60 фреймів в секунду

    //Створюємо змінні для потрібних текстур і завантажуємо відповідні текстури з файлів
    sf::Texture t1,t2,t3,t4;
    t1.loadFromFile("images/coronavirus.png");
    t2.loadFromFile("images/pole.png");
    t3.loadFromFile("images/rocket_6441.png");
    t4.loadFromFile("images/ninja-48.png");

    //створюємо 3 спрайта
    //спрайт pole з текстури t2
    //спрайт kulia з текстури t3
    //спрайт ninja з текстури t4
    //спрайт virus з текстури t1

    sf::Sprite pole(t2), kulia(t3), ninja(t4);
    sf::Sprite virus[DIM];

    n = 10; //кількість вірусів
    for(int i=1; i<=n; i++) { //в циклі всім вірусам проставляємо:
        virus[i].setTexture(t1); //текстуру t1
        life[i] = 2; //кількість життів = 2
        velo[i] = 0.1 * (rand() % 10 + 1); //випадкову швидкість
        virus[i].setPosition( rand()%700 , rand()%300 - 300 ); //позицію віруса з випадковими координатами в межах x від 0 до 699, y від -300 до -1
    }

    sf::Color initColor = virus[1].getColor(); //запам'ятаємо в змінну initColor початковий колір якогось віруса, наприклад першого

    ninja.setPosition(380,360); //встановлюємо позицію ніндзі


    dy=-5; //швидкість кулі 5 пікселів вгору
    long long iter = 0; //лічильник кроків
    while (window.isOpen()) //головний цикл програми, виконується 60 раз в секунду (бо ми встановили такий ліміт вище)
    {
        iter++; //збільшуємо лічильник кроків


        /* цей блок не чіпаємо :) - початок */
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }
        /* цей блок не чіпаємо :) - кінець */



        /* БЛОК ОБРОБКИ ПОДІЙ клавіатури, миші, джойстіка - початок*/

        //якщо натиснули клавіші вправо/вліво, то рухаємо ніндзю на 3 точки
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ninja.move(3,0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ninja.move(-3,0);

        //якщо натиснули пробіл
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            //визначаємо які зараз координати ніндзі
            x = ninja.getPosition().x;
            y = ninja.getPosition().y;
            kulia.setPosition(x+15,y); //і ставоми туди кулю (старт вильоту). +15 щоб вилітала по центру ніндзі.
        }

        /* БЛОК ОБРОБКИ ПОДІЙ клавіатури, миші, джойстіка  - кінець */







        /* БЛОК ЛОГІКИ ГРИ - початок . Сюди будем додавати логіку гри яку напридумуєм */

        //якщо ніндзя втік вліво - має з'явитись справа
        if(ninja.getPosition().x < -40)
            ninja.setPosition(768,ninja.getPosition().y );

        //якщо ніндзя втік вправо - має з'явитись зліва
        if(ninja.getPosition().x > 800)
            ninja.setPosition(0,ninja.getPosition().y );

        kulia.move(0,-5); //рухаємо кулю на dy пікселів вниз (оскільки dy від'ємне - то рухатись буде вгору)

        //кожен вірус рухаємо на його швидкість
        for(int i=1; i<=n; i++) {
            virus[i].move(0,velo[i]);
        }

        //перевіряємо усі віруси
        for(int i=1; i<=n; i++) {
            //якщо куля перетинається з i-тим вірусом
            if ( kulia.getGlobalBounds().intersects(virus[i].getGlobalBounds()) )
            {
                kulia.setPosition(-100, -100); //ховаєм кулю за межі поля
                life[i]--; //зменшуємо кількість життів у віруса

                if(life[i] <=0 ) { //якщо життів не залишилось
                    //перероджуємо вірус в нових координатах, з новими життями і новою швидкістю
                    virus[i].setPosition(rand()%700,-40);
                    life[i] = 2;
                    velo[i] = 0.1 * (rand() % 10 + 1);
                }
            }
            //якщо i-тий вірус впав нижче поля - починаємо показувати його знову згори
            if(virus[i].getPosition().y > 430) {
                virus[i].setPosition(rand()%700,-40);
            }
        }

        //пробігаємо по всім вірусам і встановлюжєм їм колір в залежності від кількості життів
        for(int i = 1; i<=n;i++) {
            //якщо лишилось 1 життя - червоний
            if(life[i]==1) virus[i].setColor(sf::Color::Red);
            //якщо є всі 2 життя - початковий
            if(life[i]==2) virus[i].setColor(initColor);
        }


        /* БЛОК ЛОГІКИ ГРИ - кінець */





        /* БЛОК ПРОМАЛЬОВКИ ВІКНА  - початок */
        window.clear(); //очищамо вікно

        window.draw(pole); //малюємо поле гри
        window.draw(ninja); //малюємо ніндзю
        window.draw(kulia); //малюємо кую
        for(int i=1; i<=n; i++)
            window.draw(virus[i]); //малюємо вірус

        window.display(); //показуємо це все на екрані
        /* БЛОК ПРОМАЛЬОВКИ ВІКНА  - кінець */

    }

    return 0;
}
