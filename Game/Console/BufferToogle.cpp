/*! This code is from this thread: https://m.cplusplus.com/forum/general/29137/
 * it is used to deactivate buffer mode in the terminal so we can get chars without pressing enter
 */
/* BufferToggle.hpp
 * @Author
 *    Luc Lieber
 *
 *    A simple class to toggle buffered input
 */

#include <termios.h>
#include <unistd.h>

class BufferToggle
{
private:
    struct termios t;

public:

    /*
     * Disables buffered input
     */

    void off(void)
    {
        tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
        t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
        tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
    }


    /*
     * Enables buffered input
     */

    void on(void)
    {
        tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
        t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
        tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
    }
};
