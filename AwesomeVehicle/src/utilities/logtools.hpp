#pragma once

#include <iostream>
#include <ostream>

#include "utilities/typedef.hpp"
namespace awe
{
using namespace std;


#define RESET        "\033[0m"
#define BLACK        "\033[30m"      /* Black */
#define RED          "\033[31m"      /* Red */
#define GREEN        "\033[32m"      /* Green */
#define YELLOW       "\033[33m"      /* Yellow */
#define BLUE         "\033[34m"      /* Blue */
#define MAGENTA      "\033[35m"      /* Magenta */
#define CYAN         "\033[36m"      /* Cyan */
#define WHITE        "\033[37m"      /* White */
#define BOLDBLACK    "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED      "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN    "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW   "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE     "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA  "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN     "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE    "\033[1m\033[37m"      /* Bold White */    


#define AWE_INFO  cout << WHITE
#define AWE_WARN  cout << YELLOW << " [WARN:] "
#define AWE_ERROR cout << RED << "[ERROR:] "

class AweLogger : public std::basic_streambuf<char>
{
public:
    explicit AweLogger(string color = "") : std::basic_streambuf<char>()
    {
        setbuf(stdout->_IO_write_ptr, 10);
        sputn("helloworld\n", 11);
        std::cout << "hello" << std::endl;
    }
};



} // namespace awe
