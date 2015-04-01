#ifndef FIELD_H
#define FIELD_H
#include <stdexcept>
#include <cstring>
#include <ctime>

/*!
 * \brief The statistcs struct
 * \details Contain how many cells were born and dead at this step.
 */
struct statistcs {
    int born;   //<How many cells were born.
    int dead;   //<How many cells were dead.
};

struct array {
    int arr[8];
    int & operator[](int i) {
        return arr[i];
    }
};

/*!
 * \brief The Field class
 */
class Field
{
public:
    /*!
     * \brief Field constructor
     * \details Construct field width*height filled with 0.
     * \param width
     * \param height
     * \param settledCels
     */
    Field(int width, int height, int settledCels);

    /*!
     * \brief Copy constuctor
     */
    Field(Field &);

    /*!
     * \brief Destructor
     */
    ~Field();

    /*!
     * \brief At function
     * \details It gives access to field cells.
     * \throw std::out_of_range
     * \param x
     * \param y
     * \return value at given coordinates
     */
    int at(int x, int y) const throw(std::out_of_range);

    /*!
     * \brief Neighbors
     * \details This function returns values of cells around given cell.
     * Function always returns 8 elements. It returns 0 for nonexistent cells.
     * \throw std::out_of_range
     * \param x
     * \param y
     * \return bool[8]
     */
    array neighbors(int x, int y) const throw(std::out_of_range);

    /*!
     * \brief Set cell value
     * \details Set new value into next generation field at given coordinates.
     * This function can extend field if needed.
     * \throw std::out_of_range
     * \param x
     * \param y
     * \param value
     */
    void set(int x, int y, bool value) throw(std::out_of_range);

    /*!
     * \brief Width
     * \return Width of current field;
     */
    int width() const;


    /*!
     * \brief Height
     * \return Height of current field;
     */
    int height() const;

    /*!
     * \brief Next step
     * \details Next generation field is current field now.
     * \return Statistic born/alive at this step.
     */
    statistcs nextStep();


private:

    enum Side{Top, Bottom, Left, Right};
    void extendField(Side side);

    void generateRandom(int settledCells);

    //текущее поколение
    int * currentGen;
    //следущее поколение
    int * nextGen;

    int currentWidth;
    int currentHeight;
    int nextWidth;
    int nextHeight;
    int xBegin;
    int yBegin;

    statistcs stat;
};

#endif // FIELD_H
