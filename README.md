# simplexC

simplexC is basically a program that interprets a optimization model with objective function, decision variables, and constraints, then run simplex to solve it

==================================================================

All you need to run the program is insert the optimization model in the file model.txt, example:

'model.txt'

Max Lucro = 10x1 + 12x2

x1 + x2 <= 100

x1 + 3x2 <= 270

obs: there are 2 example of models in the paste model for you test the program

You need to have one objective function respecting the "Max" and "Lucro" words, but you cant
type it with upper or lower case, doesnt really matter, the examples:

max lucro = 10x1 + 12x2 */CORRECT*/

MAX LUCRO = 10x1 + 12x2 */CORRECT*/

mAx lUcRo = 10x1 + 12x2 */CORRECT*/

Doesnt generate a bug at running the program.

==================================================================

After filling the model you can run main.exe and the result will print currently
at your terminal.

Example of output:

  1.000   0.000   0.000   9.000   1.000 1170.000

  0.000   1.000   0.000   1.500  -0.500  15.000

  0.000   0.000   1.000  -0.500   0.500  85.000

==================================================================

Obs1: Fill with 0 the variable that doesnt exist, if in your model the variable doesnt exist, for example:

'WRONG': 

max lucro = 2x1 + 3x2 + 4x3

x1 + x2 + x3 <= 100     

2x1 + 5x3  <= 210 /* look here that the x2 is missing*/

x2 + 9x1 <= 80    /* here x3 is missing */

to fix you need to:

'CORRECT':

max lucro = 2x1 + 3x2 + 4x3

x1 + x2 + x3 <= 100

2x1 + x2 + 0x3 <= 210

x1 + 0x2 + 0x3 <= 80


==================================================================


By now the model doesnt support real variables, however the simplex method generate results
for any kind of variable, so to outline it you can just take of the ','s multiplying for a value that take off all ','s and divide the results for 10^(n), where n represents the power that you needed to take of the ','s. Example:

max lucro = 20.5x1 + 3.2x2 + 4.6x3 /*WRONG*/ multiplying for 10 you take off all ',' :

max lucro = 205x1 + 32x2 + 46x3 /*CORRECT*/

==================================================================

