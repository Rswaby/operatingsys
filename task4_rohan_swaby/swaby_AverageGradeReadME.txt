Rohan Swaby
task 4: Average grade calculator.
Due: march 16

	For this lab the program performs average grade calculation on the minimum of 5 chapters and 2 homeworks each with 10 students.

pre condition: the program takes program name and grades.txt as parameter(min of 		       2 parameters).

Post condition: The program should output the average score from each homework 			in each chapter.

########## programing approach #############
filename: grades.txt contains 5 chapters with each chapter contain 2 hw sets
4 9  9  9   6 5   5 5   5 6
6 8  10 4    7 5   7 7   2 4
5 6  5  6    6 7   7 8   6 8
6 7  7  8    6 4   7 8   4 6
5 6  5  7    5 7   5 4   4 7
2 5  4  4    3 2   3 5   6 9
3 7  6  7    7 5   4 5   7 8
3 6  6  4    3 6   7 4   7 8
4 5  5  5    4 6   7 8   8 9
4 5  7  8    8 9   9 9   9 9  

the data from grades.txt was copies to a 2d array of size 
STUDENTS = 10 and chapters = 5 homeworks = 2.
grades[STUDENTS][chapeters*homeworks]

###### forking the managers ##############
since # of manager = # of chapters 
a loop was  used to fork n managers. the loop invarient always holds. that is 
# of managers = # of chapters = # of forks

########## forking workers for each manager ##########

for each manager: 
# of homeworks = # number of workers forked

######## calculating average ###########

for each homework we will go column by column and calculate the average.
