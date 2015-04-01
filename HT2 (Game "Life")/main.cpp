#include <iostream>
#include <ctime>
#include <stdexcept>
#include <iomanip>
#include <cstring>
#include "field.h"

using namespace std;

class InvalidInput : public exception{
public:
    InvalidInput(const string & str)throw():error_message("Invalid argument: " + str + "."){}
    virtual const char* what()const throw(){return error_message.c_str();}
private:
    string error_message;
};

//class IntegerOverload : public exception{
//public:
//    IntegerOverload(const string & str)throw():error_message("Field " + str + " is too big."){}
//    virtual const char* what()const throw(){return error_message.c_str();}
//private:
//    string error_message;
//};


enum Side{Top, Bottom, Left, Right};

////return number of dead
//int kill(bool *& field, int & height, int & widht);

////return number of born
//int birth(bool *& field, int & height, int & width);


statistcs step(Field & field);

enum InputType{Width, Height, Cells, Duration};
/*!
 * \brief input
 * \details Read one number from command line
 * \throw InvalidInput
 * \param type
 * \return entered number
 */
int input(InputType type) throw(InvalidInput);


int main()
{
    int fieldWidth;
    int fieldHeight;
    int settledCels;
    int duration;


    //Reading data
    for (int i = 1; i <= 4; i++){
        try{
            switch (i) {
            case 1:
                fieldWidth  = input(InputType::Width);
                break;
            case 2:
                fieldHeight  = input(InputType::Height);
                break;
            case 3:
                settledCels  = input(InputType::Cells);
                if (settledCels > fieldHeight * fieldWidth)
                    throw InvalidInput(to_string(settledCels) + " too many cells");
                break;
            case 4:
                duration  = input(InputType::Duration);
                break;
            }
        }
        catch (InvalidInput &e){
            cout << e.what() << endl;
            i--;
            continue;
        }
    }

    //Initialization
    Field field(fieldWidth, fieldHeight, settledCels);



//    for (int i = 0; i < fieldWidth*fieldHeight; i++)
//        cout << field[i];
//    cout << " " << fieldHeight*fieldWidth << endl;
//    extendField(field, fieldHeight, fieldWidth, Top);
//    for (int i = 0; i < fieldWidth*fieldHeight; i++)
//        cout << field[i];
//    cout << " " << fieldHeight*fieldWidth << endl;
//    extendField(field, fieldHeight, fieldWidth, Bottom);
//    for (int i = 0; i < fieldWidth*fieldHeight; i++)
//        cout << field[i];
//    cout << " " << fieldHeight*fieldWidth << endl;
//    extendField(field, fieldHeight, fieldWidth, Right);
//    for (int i = 0; i < fieldWidth*fieldHeight; i++)
//        cout << field[i];
//    cout << " " << fieldHeight*fieldWidth << endl;
//    extendField(field, fieldHeight, fieldWidth, Left);
//    for (int i = 0; i < fieldWidth*fieldHeight; i++)
//        cout << field[i];
//    cout << " " << fieldHeight*fieldWidth << endl;

    //Statistic
    const int statisticSize = duration + ((duration%10 == 0) ? 0 : 1);
    int cellsAlive[statisticSize];
    double birthDie[statisticSize];
    int bornIn10 = 0;
    int deadIn10 = 0;
    int growth = 0;
    int growthStoped = -1;

    //Work
    statistcs stat;
    for (int i = 0; i < duration; i++) {
        stat = step(field);
        bornIn10 += stat.born;
        deadIn10 += stat.dead;
        growthStoped = (stat.born - stat.dead == 0) ? i : -1;
        if ((i % 10 == 0 && i != 0) || (i == duration - 1 && i % 10 != 0)){
            cellsAlive[i/10] = (i == 0) ? settledCels :cellsAlive[i/10 - 1];
            cellsAlive[i/10] += bornIn10;
            cellsAlive[i/10] -= deadIn10;
            birthDie[i/10] = bornIn10 / ((deadIn10 != 0) ? deadIn10 : 1);
            bornIn10 = deadIn10 = 0;
        }
    }
    growth = cellsAlive[statisticSize-1] - settledCels;

    //Output
    int maxAlive = -1;
    for (int i = 0; i < statisticSize; i++){
        if(cellsAlive[i] > maxAlive){
            maxAlive = cellsAlive[i];
        }
    }
    int maxSize = to_string(maxAlive).size();
    cout << "Statistic" << endl;
    cout << "Growth: " << growth << endl;
    cout << "Cells Alive"  << endl;
    cout << "Step:  ";
    for (int i = 0; i < statisticSize; i++){
        cout  << setw(maxSize) << (i+1)*10;
    }
    cout << endl;
    cout << "Alive: ";
    for (int i = 0; i < statisticSize; i++){
        cout << setw(maxSize) << cellsAlive[i];
    }
    cout << endl;
    cout << "Born/Dead"  << endl;
    cout << "Step: ";
    for (int i = 0; i < statisticSize; i++){
        cout << setw(3) << (i+1)*10;
    }
    cout << endl;
    cout << "B/D:  ";
    for (int i = 0; i < statisticSize; i++){
        cout << setw(3) << birthDie[i];
    }
    cout << endl;
    if (growthStoped != -1){
        cout << "Growth stopped at step " << growthStoped << endl;
    }

    //Free memory;
    //delete field;
    return 0;
}

statistcs step(Field & field) {
    for (int y = 0; y < field.height(); y++){
        for (int x  = 0; x < field.width(); x++) {
            array neighbors = field.neighbors(x, y);
            int cellsAlive = 0;
            for (int i = 0; i < 8; i++) {
                if(neighbors[i] == 1)
                    cellsAlive++;
            }
            if (field.at(x, y)) {
                if (cellsAlive == 3 || cellsAlive == 2){
                    field.set(x, y, true);
                } else {
                    field.set(x, y, false);
                }
            } else {
                if (cellsAlive == 3){
                    field.set(x, y, true);
                } else {
                    field.set(x, y, false);
                }
            }
        }
    }
    return field.nextStep();
}

int input(InputType type) throw(InvalidInput){
    string text;
    switch (type) {
    case Width:
        text = "field width";
        break;
    case Height:
        text = "field height";
        break;
    case Cells:
        text = "number of settled cels";
        break;
    case Duration:
        text = "number of steps";
        break;
    }

    cout << "Please enter " + text + ":";

    size_t *pos = new size_t;
    int value;
    string str;
    cin >> str;

    try{
        value = stoi(str, pos);
        if (*pos != str.length() || value <= 0)
            throw InvalidInput(text + " - " + str);
    }
    catch (exception) {
        throw InvalidInput(text + " - " + str);
    }
    return value;
}
