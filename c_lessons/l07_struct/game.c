#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // для sleep() если понадобится

#define WIDTH 20
#define HEIGHT 20

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pos;
} Player;

typedef struct {
    Position pos;
    int strength;
} Enemy;

typedef struct {
    int width;
    int height;
    Player player;
    Enemy enemy;
    Position exitPos;
} Room;

void clearScreen() {
    // Очистка экрана для MacOS/Linux с помощью ANSI-последовательностей
    printf("\033[H\033[J");
}

Room createRoom(int width, int height) {
    Room r;
    r.width = width;
    r.height = height;
    // Инициализация игрока
    r.player.pos.x = 0;
    r.player.pos.y = 0;

    // Инициализируем единственного врага
    r.enemy.pos.x = rand() % width;
    r.enemy.pos.y = rand() % height;
    r.enemy.strength = 1;

    // Выход в правом нижнем углу
    r.exitPos.x = width - 1;
    r.exitPos.y = height - 1;

    return r;
}

void printRoom(Room r) {
    char map[HEIGHT][WIDTH];
    // Заполняем карту точками
    for (int i = 0; i < r.height; i++) {
        for (int j = 0; j < r.width; j++) {
            map[i][j] = '.';
        }
    }

    // Размещаем игрока
    map[r.player.pos.y][r.player.pos.x] = 'P';

    // Размещаем врага
    map[r.enemy.pos.y][r.enemy.pos.x] = 'E';

    // Размещаем выход
    map[r.exitPos.y][r.exitPos.x] = 'X';

    // Выводим карту
    for (int i = 0; i < r.height; i++) {
        for (int j = 0; j < r.width; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void movePlayer(Room* r, int dx, int dy) {
    int newX = r->player.pos.x + dx;
    int newY = r->player.pos.y + dy;
    if (newX < 0 || newX >= r->width || newY < 0 || newY >= r->height) {
        // Не выходим за пределы
        return;
    }
    r->player.pos.x = newX;
    r->player.pos.y = newY;
}

void moveEnemy(Room* r) {
    // Случайное направление по осям X и Y: -1, 0 или 1
    int dx = (rand() % 3) - 1; // будет -1, 0 или 1
    int dy = (rand() % 3) - 1;

    int newX = r->enemy.pos.x + dx;
    int newY = r->enemy.pos.y + dy;
    // Проверяем границы
    if (newX >= 0 && newX < r->width && newY >= 0 && newY < r->height) {
        r->enemy.pos.x = newX;
        r->enemy.pos.y = newY;
    }
    // Если движение за пределы поля - враг не двигается
}

int checkVictory(Room* r) {
    if (r->player.pos.x == r->exitPos.x && r->player.pos.y == r->exitPos.y) {
        return 1;
    }
    return 0;
}

int checkCatch(Room* r) {
    // Проверяем, совпадают ли координаты игрока и врага
    if (r->player.pos.x == r->enemy.pos.x && r->player.pos.y == r->enemy.pos.y) {
        return 1; // Противник догнал игрока
    }
    return 0;
}

int main() {
    srand((unsigned)time(NULL));
    Room currentRoom = createRoom(WIDTH, HEIGHT);

    while (1) {
        clearScreen();
        printRoom(currentRoom);
        printf("Move (WASD then ENTER): ");

        char c = getchar();
        // Считываем возможный лишний ENTER, если есть
        while (getchar() != '\n');

        int dx = 0, dy = 0;
        if (c == 'w' || c == 'W') dy = -1;
        if (c == 's' || c == 'S') dy = 1;
        if (c == 'a' || c == 'A') dx = -1;
        if (c == 'd' || c == 'D') dx = 1;

        movePlayer(&currentRoom, dx, dy);
        moveEnemy(&currentRoom);

        // Проверяем, не догнал ли нас противник после обоих движений
        if (checkCatch(&currentRoom)) {
            clearScreen();
            printRoom(currentRoom);
            printf("You Lose! The enemy caught you.\n");
            break;
        }

        if (checkVictory(&currentRoom)) {
            printf("Victory!\n");
            break;
        }
    }

    return 0;
}
