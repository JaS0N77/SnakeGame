#include "Game.h"

SnakeGame::SnakeGame(int w, int h) : width(w), height(h) 
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailX = new int[width * height];
    tailY = new int[width * height];
    nTail = 0;
}

SnakeGame::~SnakeGame() 
{
    delete[] tailX;
    delete[] tailY;
}

void SnakeGame::Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void SnakeGame::SetSnakeColor()
{
    while (true)
    {
        system("cls");
        cout << "===== COLOR ====" << endl;
        cout << "[1] Blue" << endl;
        cout << "[2] Green" << endl;
        cout << "[3] Cyan" << endl;
        cout << "[4] Red" << endl;
        cout << "[5] Purple" << endl;
        cout << "[6] Yellow" << endl;
        cout << "[7] White" << endl;
        cout << "[8] Gray" << endl;
        cout << "[0] Quit" << endl;
        cout << endl;

        cout << "Choose a color: ";
        int color;
        cin >> color;
        switch (color)
        {
        case 1:
            snakeColor = 1;
            break;
        case 2:
            snakeColor = 2;
            break;
        case 3:
            snakeColor = 3;
            break;
        case 4:
            snakeColor = 4;
            break;
        case 5:
            snakeColor = 5;
            break;
        case 6:
            snakeColor = 6;
            break;
        case 7:
            snakeColor = 7;
            break;
        case 8:
            snakeColor = 8;
            break;
        case 0:
            return;
        default:
            break;
        }

    }
}

void SnakeGame::Draw() 
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
    {
        cout << "=";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "|";
            }
            if (i == y && j == x)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeColor);
                cout << "O";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "*";
            }
            else
            {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeColor);
                        cout << "o";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
                        printTail = true;
                    }
                }
                if (!printTail)
                {
                    cout << " ";
                }
            }

            if (j == width - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "=";
    }
    cout << endl;

    cout << "Score:" << score << endl;
}

void SnakeGame::Input()
{
    string savePath = "Save.bin";
    SnakeGame sk(50, 30);
    if (_kbhit()) 
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'c':
            sk.SaveInFile(savePath);
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void SnakeGame::Algorithm() 
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) 
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) 
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x >= width)
    {
        x = 0;
    }
    else if (x < 0)
    {
        x = width - 1;
    }
    if (y >= height)
    {
        y = 0;
    }
    else if (y < 0)
    {
        y = height - 1;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) 
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}


void SnakeGame::SaveInFile(const string& fileName) 
{
    ofstream outFile(fileName,ios::out | ios::binary);

    if (!outFile) 
    {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    outFile.write(reinterpret_cast<char*>(&width), sizeof(width));
    outFile.write(reinterpret_cast<char*>(&height), sizeof(height));
    outFile.write(reinterpret_cast<char*>(&x), sizeof(x));
    outFile.write(reinterpret_cast<char*>(&y), sizeof(y));
    outFile.write(reinterpret_cast<char*>(&fruitX), sizeof(fruitX));
    outFile.write(reinterpret_cast<char*>(&fruitY), sizeof(fruitY));
    outFile.write(reinterpret_cast<char*>(&score), sizeof(score));
    outFile.write(reinterpret_cast<char*>(&nTail), sizeof(nTail));
    outFile.write(reinterpret_cast<char*>(&dir), sizeof(dir));
    outFile.write(reinterpret_cast<char*>(tailX), nTail * sizeof(int));
    outFile.write(reinterpret_cast<char*>(tailY), nTail * sizeof(int));


    outFile.close();
}

void SnakeGame::LoadFromFile(const string& fileName)
{
    ifstream inFile(fileName, ios::in | ios::binary);

    if (!inFile)
    {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    inFile.read(reinterpret_cast<char*>(&width), sizeof(width));
    inFile.read(reinterpret_cast<char*>(&height), sizeof(height));
    inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
    inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
    inFile.read(reinterpret_cast<char*>(&fruitX), sizeof(fruitX));
    inFile.read(reinterpret_cast<char*>(&fruitY), sizeof(fruitY));
    inFile.read(reinterpret_cast<char*>(&score), sizeof(score));
    inFile.read(reinterpret_cast<char*>(&nTail), sizeof(nTail));
    inFile.read(reinterpret_cast<char*>(&dir), sizeof(dir));
    inFile.read(reinterpret_cast<char*>(tailX), nTail * sizeof(int));
    inFile.read(reinterpret_cast<char*>(tailY), nTail * sizeof(int));

    isLoadedFromFile = true;

    inFile.close();

}
void SnakeGame::RunGame() 
{
    if (!isLoadedFromFile) 
    {
        Setup();
        isLoadedFromFile = false;
    }
    while (!gameOver)
    {
        Draw();
        Input();
        Algorithm();
        Sleep(50);
    }

    system("cls");
    cout << "Game Over!\nYour score is: " << score << endl;
    Sleep(2000);
}


void textColor()
{
    while (true)
    {   system("cls");
        cout << "========= COLORS =========" << endl;
        cout << "[1] Blue" << endl;
        cout << "[2] Green" << endl;
        cout << "[3] Red" << endl;
        cout << "[4] Purple" << endl;
        cout << "[5] Yellow" << endl;
        cout << "[6] White" << endl;
        cout << "[7] Gray" << endl;
        cout << "[8] Black" << endl;
        cout << "[0] Quit" << endl;
        cout << "==========================" << endl;
        cout << endl;

        int choice;
        cout << "Choose an option: ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            system("Color 1");
            break;
        case 2:
            system("Color 2");
            break;
        case 3:
            system("Color 4");
            break;
        case 4:
            system("Color 5");
            break;
        case 5:
            system("Color 6");
            break;
        case 6:
            system("Color 7");
            break;
        case 7:
            system("Color 8");
            break;
        case 8:
            system("Color 07");
            break;
        case 0:
            return;
        default:
            return;
        }
    }

}

void backColor()
{
    while (true)
    {
        system("cls");
        cout << "========= COLORS =========" << endl;
        cout << "[1] Blue" << endl;
        cout << "[2] Green" << endl;
        cout << "[3] Red" << endl;
        cout << "[4] Purple" << endl;
        cout << "[5] Yellow" << endl;
        cout << "[6] White" << endl;
        cout << "[7] Gray" << endl;
        cout << "[8] Black" << endl;
        cout << "[0] Quit" << endl;
        cout << "==========================" << endl;
        cout << endl;

        int choice;
        cout << "Choose an option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("Color 18");
            break;
        case 2:
            system("Color 26");
            break;
        case 3:
            system("Color 40");
            break;
        case 4:
            system("Color 57");
            break;
        case 5:
            system("Color 60");
            break;
        case 6:
            system("Color 72");
            break;
        case 7:
            system("Color 87");
            break;
        case 8:
            system("Color 07");
            break;
        case 0:
            return;
        default:
            return;
        }
    }

}


int main() 
{
    string loadPath = "Save.bin";
    SnakeGame snakeGame(50, 25);
    while (true)
    {
        system("cls");
        cout << "=========================== MENU ===========================" << endl;
        cout << "[1] Start new game" << endl;
        cout << "[2] Load game" << endl;
        cout << "[3] Change the text color" << endl;
        cout << "[4] Change the background color" << endl;
        cout << "[5] Change the snake color" << endl;
        cout << "============================================================" << endl;
        cout << endl;

        int choice;
        cout << "Choose an option: ";
        cin >> choice;



        switch (choice)
        {
        case 1:
            snakeGame.RunGame();
            break;
        case 2:
            snakeGame.LoadFromFile(loadPath);
            snakeGame.RunGame();
            break;
        case 3:
            textColor();
            break;
        case 4:
            backColor();
            break;
        case 5:
            snakeGame.SetSnakeColor();
            break;
        default:
            break;
        }

    }
    return 0;
}