/** @file Utils.h
 * 
 * @brief A header file including some utilities funtions. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Sep 8, 2021       
 *
 */

#ifndef UTILS_H
#define UTILS_H

//Map function
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif /* UTILS_H */

/*** end of file ***/