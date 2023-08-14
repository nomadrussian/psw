/* labelHandler.c - working with data.
 * -----------------------------------------------
 * You can use it to save your passwords and then
 * access them later when you need.
 * 
 * You just type in:
 *     $ psw save <label> <password>
 *
 * -----------------------------------------------
 * How it shows a datum stored on your hard drive:
 * 
 * You just type in:
 *     $ psw recall <label> 
 * 
 * The output is simple:
 *     <label>: <login> | <password>
 *
 * To see your label list:
 *     $ psw lb
 *
 * To see your label list with your passwords:
 *     $ psw lb_unsafe
 *
 * -----------------------------------------------
 * To remove the label use:
 *     $ psw remove <label>
 *
 * BE CAREFUL: The action CANNOT be undone!
 * -------------------------------------------- */

#include "labelHandler.h"
