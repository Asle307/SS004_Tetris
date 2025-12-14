#include <SFML/Graphics.hpp> // Thư viện đồ họa SFML
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <algorithm>      // Thêm để đảm bảo hàm max() hoạt động

using namespace std;
using namespace sf; // Sử dụng namespace của SFML

const int H = 20; 
const int W = 15; 

// KHAI BÁO KÍCH THƯỚC MỘT Ô GẠCH (PIXEL)
const int TILE_SIZE = 30; 

char board[H][W] = {};
int x = 4, y = 0;
int speed = 400; // Đơn vị này sẽ được chuyển thành thời gian (giây) trong SFML

// --- PHẦN CLASS VÀ LOGIC GAME (GIỮ NGUYÊN HOÀN TOÀN) ---

class Piece {
public:
    char shape[4][4];

    Piece() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = ' ';
    }

    virtual ~Piece() {}

    virtual void rotate(int currentX, int currentY) {
        char temp[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[j][3 - i] = shape[i][j];
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (temp[i][j] != ' ') {
                    int tx = currentX + j;
                    int ty = currentY + i;
                    if (tx < 1 || tx >= W - 1 || ty >= H - 1) return; 
                    if (board[ty][tx] != ' ') return; 
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = temp[i][j];
            }
        }
    }
};

class IPiece : public Piece {
public:
    IPiece() {
        shape[0][1] = 'I'; shape[1][1] = 'I'; shape[2][1] = 'I'; shape[3][1] = 'I';
    }
};

class OPiece : public Piece {
public:
    OPiece() {
        shape[1][1] = 'O'; shape[1][2] = 'O';
        shape[2][1] = 'O'; shape[2][2] = 'O';
    }
    void rotate(int currentX, int currentY) override {
    }
};

class TPiece : public Piece {
public:
    TPiece() {
        shape[1][1] = 'T';
        shape[2][0] = 'T'; shape[2][1] = 'T'; shape[2][2] = 'T';
    }
};

class SPiece : public Piece {
public:
    SPiece() {
        shape[1][1] = 'S'; shape[1][2] = 'S';
        shape[2][0] = 'S'; shape[2][1] = 'S';
    }
};

class ZPiece : public Piece {
public:
    ZPiece() {
        shape[1][0] = 'Z'; shape[1][1] = 'Z';
        shape[2][1] = 'Z'; shape[2][2] = 'Z';
    }
};

class JPiece : public Piece {
public:
    JPiece() {
        shape[1][0] = 'J';
        shape[2][0] = 'J'; shape[2][1] = 'J'; shape[2][2] = 'J';
    }
};

class LPiece : public Piece {
public:
    LPiece() {
        shape[1][2] = 'L';
        shape[2][0] = 'L'; shape[2][1] = 'L'; shape[2][2] = 'L';
    }
};

Piece* currentPiece = nullptr;

Piece* createRandomPiece() {
    int r = rand() % 7;
    switch (r) {
        case 0: return new IPiece();
        case 1: return new OPiece();
        case 2: return new TPiece();
        case 3: return new SPiece();
        case 4: return new ZPiece();
        case 5: return new JPiece();
        case 6: return new LPiece();
        default: return new IPiece();
    }
}

// CÁC HÀM CONSOLE ĐÃ BỊ LOẠI BỎ: gotoxy(), setColor(), draw()

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->shape[i][j] != ' ' && y + j < H)
                board[y + i][x + j] = ' ';
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->shape[i][j] != ' ')
                board[y + i][x + j] = currentPiece->shape[i][j];
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = '#';
            else board[i][j] = ' ';
}
bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->shape[i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

void SpeedIncrement()
{
    // Đã thay thế hàm max() bằng cách kiểm tra if/else để tránh lỗi phụ thuộc thư viện
    if (speed > 100) speed -= 30;
}

void removeLine(){
    for(int i = H - 2; i > 0; i--){
        bool isFull = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') {
                isFull = false;
            }
        }
        if (isFull) {
            for (int k = i; k > 0; k--) {
                for (int j = 1; j < W - 1; j++) {
                    if (k != 1) {
                        board[k][j] = board[k - 1][j];
                    }
                    else {
                        board[k][j] = ' ';
                    }
                }
            }
            i++;
            // Ở bước 2.4 (Âm thanh), sẽ thêm lệnh phát nhạc ăn điểm tại đây
            SpeedIncrement();
        }    
    }
}

Color getColor(char c) {
    switch (c) {
        case 'I': return Color::Cyan;
        case 'J': return Color::Blue;
        case 'L': return Color(255, 165, 0);
        case 'O': return Color::Yellow;
        case 'S': return Color::Green;
        case 'T': return Color(128, 0, 128);
        case 'Z': return Color::Red;
        case '#': return Color(100, 100, 100);
        default:  return Color::Black;
    }
}

// --- VÒNG LẶP CHÍNH (SẼ ĐƯỢC VIẾT LẠI HOÀN TOÀN Ở BƯỚC 2.2) ---

int main()
{
    // --- KHAI BÁO BAN ĐẦU (GIỮ NGUYÊN) ---
    RenderWindow window(VideoMode(Vector2u(W * TILE_SIZE, H * TILE_SIZE)),"SS008");
    srand(time(0));
    currentPiece = createRandomPiece();
    initBoard();
    Clock clock;
    while(window.isOpen()) {
        // ================= EVENT =================
        while (auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>()) window.close();
            
        }

        // ================= TIME =================
        float dt = clock.getElapsedTime().asMilliseconds();

        // ================= INPUT =================
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && canMove(-1, 0))
            x--;

        if (Keyboard::isKeyPressed(Keyboard::Key::D) && canMove(1, 0))
            x++;

        if (Keyboard::isKeyPressed(Keyboard::Key::S) && canMove(0, 1))
            y++;

        if (Keyboard::isKeyPressed(Keyboard::Key::W))
            currentPiece->rotate(x, y);


        // ================= GRAVITY =================
        if (dt > speed)
        {
            clock.restart();

            if (canMove(0, 1))
            {
                y++;
            }
            else
            {
                block2Board();
                removeLine();
                
                delete currentPiece;
                currentPiece = createRandomPiece();

                x = 4;
                y = 0;
            }
        }

        window.clear(Color::Black);

        // Vẽ board
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (board[i][j] != ' ')
                {
                    RectangleShape rect(
                        Vector2f(TILE_SIZE - 1, TILE_SIZE - 1)
                    );
                    rect.setPosition(
                        Vector2f( j * TILE_SIZE,  i * TILE_SIZE)
                    );
                    rect.setFillColor(getColor(board[i][j]));
                    window.draw(rect);
                }
            }
        }

        // Vẽ block đang rơi
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (currentPiece->shape[i][j] != ' ')
                {
                    RectangleShape rect(
                        Vector2f(TILE_SIZE - 1, TILE_SIZE - 1)
                    );
                    rect.setPosition(
                        Vector2f( (x + j) * TILE_SIZE,  (y + i) * TILE_SIZE)
                    );
                    rect.setFillColor(
                        getColor(currentPiece->shape[i][j])
                    );
                    window.draw(rect);
                }
            }
        }
        window.display();
    }
    
    // Ở bước 2.2, chúng ta sẽ thay thế toàn bộ vòng lặp while(1) cũ bằng:
    // 1. Tạo RenderWindow
    // 2. Tạo Clock
    // 3. Vòng lặp while(window.isOpen())
    // 4. Xử lý Input bằng sf::Event
    // 5. Thay thế Sleep(speed) bằng logic thời gian (timer)
    // 6. Viết hàm vẽ mới thay thế draw() cũ

    return 0;
}
