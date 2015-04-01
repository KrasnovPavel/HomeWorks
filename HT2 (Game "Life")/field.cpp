#include "field.h"

Field::Field(int width, int height, int settledCels)
{
    currentWidth  = nextWidth  = width;
    currentHeight = nextHeight = height;
    xBegin = 0;
    yBegin = 0;
    stat.born = 0;
    stat.dead = 0;

    currentGen = new int[currentHeight * currentWidth];
    nextGen    = new int[nextHeight * nextWidth];
    memset(nextGen, 0, sizeof(bool) * nextWidth * nextHeight);
    memset(currentGen, 0, sizeof(bool) * currentWidth * currentHeight);

    generateRandom(settledCels);
}

Field::Field(Field &other)
{
    currentWidth  = other.currentWidth;
    nextWidth  = other.nextWidth;
    currentHeight = other.currentHeight;
    nextHeight = other.nextHeight;
    xBegin = other.xBegin;
    yBegin = other.yBegin;
    stat.born = other.stat.born;
    stat.dead = other.stat.dead;

    currentGen = new int[currentHeight * currentWidth];
    nextGen    = new int[nextHeight * nextWidth];
    memset(nextGen, 0, sizeof(int) * nextWidth * nextHeight);
    memset(currentGen, 0, sizeof(int) * currentWidth * currentHeight);
    for (int y = 0; y < nextHeight; y++){
        for (int x = 0; x < nextWidth; x++){
            nextGen[y * nextWidth + x] = other.nextGen[y * nextWidth + x];
        }
    }
    for (int y = 0; y < currentHeight; y++){
        for (int x = 0; x < currentWidth; x++){
            currentGen[y * currentWidth + x] = other.currentGen[y * currentWidth + x];
        }
    }

}

Field::~Field()
{
    delete[] nextGen;
    delete[] currentGen;
}

int Field::at(int x, int y) const throw(std::out_of_range)
{
    if (x >= currentWidth || y >= currentHeight)
        throw std::out_of_range("Out of range exception in function \"at\"");

    return currentGen[y * currentHeight + x];
}

array Field::neighbors(int x, int y) const throw(std::out_of_range)
{
    if (x >= currentWidth || y >= currentHeight)
        throw std::out_of_range("Out of range exception in function \"at\"");

    array result;

    if(x != 0 && y != 0)
        result[0] = currentGen[(y - 1) * currentWidth + (x - 1)];
    if(x != 0)
        result[1] = currentGen[y * currentWidth + (x - 1)];
    if(x != 0 && y != currentHeight-1)
        result[2] = currentGen[(y + 1) * currentWidth + (x - 1)];
    if(y != currentHeight-1)
        result[3] = currentGen[(y + 1) * currentWidth + x];
    if(x != currentWidth-1 && y != currentHeight-1)
        result[4] = currentGen[(y + 1) * currentWidth + (x + 1)];
    if(x != currentWidth-1)
        result[5] = currentGen[y * currentWidth + (x + 1)];
    if(x != currentWidth-1 && y != 0)
        result[6] = currentGen[(y - 1) * currentWidth + (x + 1)];
    if(y != 0)
        result[7] = currentGen[(y - 1) * currentWidth + x];

    return result;
}

void Field::set(int x, int y, bool value) throw(std::out_of_range)
{
    if (x >= currentWidth || y >= currentHeight)
        throw std::out_of_range("Out of range exception in function \"set\"");

    if (x + xBegin == 0)
        extendField(Left);
    else if (x + xBegin == nextWidth - 1)
        extendField(Right);
    if (y + yBegin == 0)
        extendField(Top);
    else if (y + yBegin == nextHeight - 1)
        extendField(Bottom);

    if (this->at(x, y) != value) {
        if (value)
            stat.born++;
        else
            stat.dead++;
    }

    currentGen[(y + yBegin) * currentWidth + (x + xBegin)] = value;
}

int Field::width() const
{
    return currentWidth;
}

int Field::height() const
{
    return currentHeight;
}

statistcs Field::nextStep()
{
    currentHeight = nextHeight;
    currentWidth  = nextWidth;

    if (currentGen != nullptr){
        delete[] currentGen;
        currentGen = nullptr;
    }
    currentGen = nextGen;

    nextGen = new int[currentHeight * currentWidth];
    memset(nextGen, 0, sizeof(int) * currentHeight * currentWidth);

    statistcs result = stat;
    stat.born = 0;
    stat.dead = 0;
    return result;
}

void Field::extendField(Field::Side side)
{
    int oldWidth  = nextWidth;
    int oldHeight = nextHeight;
    int newXBegin = 0;
    int newYBegin = 0;

    switch (side) {
    case Right:
        nextWidth++;
        break;
    case Left:
        nextWidth++;
        xBegin++;
        newXBegin = 1;
        break;
    case Bottom:
        nextHeight++;
        break;
    case Top:
        nextHeight++;
        yBegin++;
        newXBegin = 1;
        break;
    }

    int * newField = new int[nextWidth * nextHeight];
    memset(newField, 0, sizeof(int) * nextWidth * nextHeight);

    for (int y = 0; y < oldHeight; y++){
        for (int x = 0; x < oldWidth; x++){
            newField[(y + newYBegin) * nextWidth + (x + newXBegin)] =
                    nextGen[y * currentWidth + x];
        }
    }

    delete[] nextGen;
    nextGen = newField;
}

void Field::generateRandom(int settledCells)
{
    srand(time(0));
    int x = rand() % nextWidth;
    int y = rand() % nextHeight;
    for (int i = 0; i < settledCells; i++) {
        while (nextGen[y * nextWidth + x]) {
            x = rand() % nextWidth;
            y = rand() % nextHeight;
        }
    }
    extendField(Top);
    extendField(Left);
    extendField(Bottom);
    extendField(Right);
    nextStep();
}
