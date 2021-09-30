/** @file KPD_confing.h
 * 
 * @brief A header file including configurations for KPD controlling. 
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Aug 18, 2021       
 *
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define NOT_PRESSED 101

#define KPD_U8ARR         \
{                         \
    {'7', '8', '9',  '/'  }, \
    {'4', '5', '6', 'x'}, \
    {'1', '2', '3', '-'}, \
    {'O', '0', '=', '+'}  \
                          \
}

#define KPD_u8PORT Port_D

/*The the COLUMN pins  -Output-*/
#define KPD_u8COLUMN0_PIN Pin_0
#define KPD_u8COLUMN1_PIN Pin_1
#define KPD_u8COLUMN2_PIN Pin_2
#define KPD_u8COLUMN3_PIN Pin_3

/*The the ROW pins -Input-*/

#define KPD_u8ROW0_PIN Pin_4
#define KPD_u8ROW1_PIN Pin_5
#define KPD_u8ROW2_PIN Pin_6
#define KPD_u8ROW3_PIN Pin_7

#endif /* KPD_CONFIG_H */

/*** end of file ***/
