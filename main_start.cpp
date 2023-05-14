#include <Grapic.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace grapic;
using namespace std;

const int WIDTH = 1024;
const int HEIGHT = 768;
const int PIPE_WIDTH = 50;
const int PIPE_GAP = 125;
const int PIPE_SPEED = 1;
const float GRAVITY = -0.3f;
const float JUMP_SPEED = 3.0f;
const int FLOOR = 64; // Hauteur du sol du background en pixel

int backgroundOffset1 = 0;
int backgroundOffset2 = WIDTH;

//-------------------------------------------------------------------------
struct Complex
{
    float x,y;
};

Complex make_complex(float r, float i)
{
    Complex c;
    c.x = r;
    c.y = i;
    return c;
}

Complex operator+(Complex a, Complex b)
{
    Complex c = make_complex( a.x+b.x, a.y+b.y );
    return c;
}

Complex operator-(Complex a, Complex b)
{
    Complex c = make_complex( a.x-b.x, a.y-b.y );
    return c;
}

Complex operator*(float a, Complex b)
{
    Complex c = make_complex( a*b.x, a*b.y );
    return c;
}
Complex operator/(Complex b, float d)
{
    Complex c = make_complex( b.x/d, b.y/d );
    return c;
}

Complex operator*(Complex a, Complex b)
{
    Complex c = make_complex( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x );
    return c;
}
//-------------------------------------------------------------------------

struct Bird // Déclaration de la structure de l'oiseau
{
    Complex c;
    float velocity;
    Image im_bird;
};

void init(Bird& b)
{
    b.c = make_complex(WIDTH/2, HEIGHT/2);
    b.velocity = 0;
    b.im_bird = image("data/flappybird/bird.png");
}

void draw(Bird& b)
{
    image_draw(b.im_bird, b.c.x - 16, b.c.y - 16); // Affichage du sprite de l'oiseau aux coordonnées du complex
}

void update(Bird& b, bool& gameOver) {
    const float d = 2.f;
    if (!gameOver) {
        b.velocity += GRAVITY;
        b.c.y += b.velocity;
        if (isKeyPressed(SDLK_SPACE)) {
            b.velocity = JUMP_SPEED;
        }
        if (b.c.y < FLOOR) { // Collision avec le sol
            gameOver = true;
        }
    }
}

struct Pipe { // Déclaration de la structure des tuyaux
    int x, y, height;
    bool passed;
    Image im_pipe;
};

void generatePipes(vector<Pipe>& pipes) {
    // Génère une paire de tuyaux
    Pipe topPipe, bottomPipe;

    // Définit la hauteur des tuyaux aléatoirement
    int minHeight = 100;
    int maxHeight = HEIGHT - PIPE_GAP - minHeight;
    int height = minHeight + rand() % maxHeight;

    // Définit la position des tuyaux
    topPipe.x = WIDTH;
    topPipe.y = 0;
    topPipe.height = height;
    topPipe.im_pipe = image("data/flappybird/pipe_top.png");

    bottomPipe.x = WIDTH;
    bottomPipe.y = height + PIPE_GAP;
    bottomPipe.height = HEIGHT - bottomPipe.y;
    bottomPipe.im_pipe = image("data/flappybird/pipe_bottom.png");

    // Ajoute les tuyaux au vecteur
    pipes.push_back(topPipe);
    pipes.push_back(bottomPipe);
}

void movePipes(vector<Pipe>& pipes, bool gameOver) {
    // Déplace les tuyaux vers la gauche
    if (!gameOver) {
        for (int i = 0; i < pipes.size(); i++) {
            pipes[i].x -= PIPE_SPEED;
        }

        // Supprime les tuyaux qui sont hors de l'écran
        if (pipes.size() > 0 && pipes[0].x + PIPE_WIDTH < 0) {
            pipes.erase(pipes.begin(), pipes.begin() + 2);
        }

        // Met à jour le décalage des fonds d'écran
        // Nécessité de 2 background pour les afficher à la suite lorsqu'on déplace le premier avec les tuyaux
        backgroundOffset1 -= PIPE_SPEED;
        backgroundOffset2 -= PIPE_SPEED;
        if (backgroundOffset1 <= -WIDTH) {
            backgroundOffset1 = WIDTH;
        }
        if (backgroundOffset2 <= -WIDTH) {
            backgroundOffset2 = WIDTH;
        }
    }
}

void drawPipes(vector<Pipe>& pipes) {
    // Dessine les tuyaux à l'écran
    for (int i = 0; i < pipes.size(); i += 2) {
        // Dessine le tuyau du haut
        image_draw(pipes[i].im_pipe, pipes[i].x, pipes[i].y + FLOOR, PIPE_WIDTH, pipes[i].height - FLOOR);

        // Dessine le tuyau du bas
        image_draw(pipes[i + 1].im_pipe, pipes[i + 1].x, pipes[i + 1].y, PIPE_WIDTH, pipes[i + 1].height);
    }
}

bool checkCollision(Bird& bird, vector<Pipe>& pipes) {
    // Vérifie la collision avec chaque paire de tuyaux
    for (int i = 0; i < pipes.size(); i += 2) {
        // Vérifie la collision avec le tuyau du haut
        if (bird.c.x + 15 > pipes[i].x && bird.c.x - 15 < pipes[i].x + PIPE_WIDTH && bird.c.y - 15 < pipes[i].height) {
            return true;
        }

        // Vérifie la collision avec le tuyau du bas
        if (bird.c.x + 15 > pipes[i + 1].x && bird.c.x - 15 < pipes[i + 1].x + PIPE_WIDTH && bird.c.y + 15 > pipes[i + 1].y) {
            return true;
        }
    }

    return false;
}

int main(int , char** )
{
    bool stop=false;
    bool gameOver = false;
    srand(time(NULL));
    winInit("FlappyBird", WIDTH, HEIGHT );
    Image background = image("data/flappybird/background.jpg");
    image_draw(background, backgroundOffset1, 0);
    image_draw(background, backgroundOffset2, 0);

    vector<Pipe> pipes;

    Menu menu;
    menu_add( menu, "Bird");
    Bird b;
    init(b);
    while (!stop) {
    setKeyRepeatMode(true);
    winClear();
    switch (menu_select(menu)) {
        case 0:
            setKeyRepeatMode(true);
            if (pipes.size() == 0 || pipes[pipes.size() - 1].x < WIDTH - PIPE_WIDTH - PIPE_GAP) 
            {
                generatePipes(pipes);
            }

            if (!gameOver) 
            {
                movePipes(pipes, gameOver);
                if (checkCollision(b, pipes)) {
                    gameOver = true;
                }
                else {
                    image_draw(background, backgroundOffset1, 0);
                    image_draw(background, backgroundOffset2, 0);
                }
                drawPipes(pipes);
                update(b, gameOver);
                draw(b);
            }
            else
            {
                fontSize(50);
                print(WIDTH / 2 - 100, HEIGHT / 2, "Game Over");
            }

            if (gameOver && isKeyPressed(SDLK_r))
            {
                gameOver = false;
                // Réinitialiser le jeu
                init(b);
                pipes.clear();
            }

            delay(10); // Délai pour éviter au tuyaux d'aller trop vite pour le joueur (modifiable pour rendre le jeu plus lent)
            break;
    }
    menu_draw(menu);
    stop = winDisplay();
    }
    return 0;
}