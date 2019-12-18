@echo off
color 02
:MAIN
set /a var=0
echo.
echo.
echo.
echo Welcome to a CIS 151 quiz game.
echo.
echo.Please only use capital letters for your answer!!
echo.
echo To start the game, type A and press ENTER.

set /p input=COMMAND?
if %input%==A goto GAME

:GAME
cls
echo.
echo.
echo.
echo Who is your favorite Command Line instructor?
echo.
echo A. Bugs Bunny
echo B. Your Current Instructor
echo C. your dog
echo D. some dude online in Kansas
echo.
set /p input=ANSWER?
if %input%==B goto right
goto WRONG

:right
set /a var+=1
echo Great Job !!  You scored a point !!
pause
goto 2

:WRONG
echo Sorry, that is incorrect. Better luck next time .
pause
REM (this pauses the program until a key is pressed)
goto 2

:2
cls
echo.
echo.
echo.
echo What Chapter is your favorite?
echo.
echo A. Chapter 4 - DOS
echo B. Chapter 1 - History
echo C. Chapter 3 - Virtual Desktop
echo D. Chapter 2 - Virus
echo.
set /p input=ANSWER?
if %input%==A goto right
goto WRONG

:right
set /a var+=1
echo Great Job !!  You scored a point !!
pause
goto 3

:WRONG
echo Yikes, that is incorrect. Better luck next time .
pause
REM (this pauses the program until a key is pressed)
goto 3

:3
cls
echo.
echo.
echo.
echo Which one is more user friendly?
echo.
echo A. Command Line
echo B. Batch Files
echo C. Windows OS
echo D. Unix
echo.
set/p input=ANSWER?
if %input%==C goto right
goto WRONG

:right
set /a var+=1
echo Great Job !!  You scored a point !!
pause
goto 4

:WRONG
echo Sorry, that is incorrect. Better luck next time .
pause
REM (this pauses the program until a key is pressed)
goto 4

:4
CLS
echo.
echo.
echo.
echo.
color 64 
echo Your score is ... %var%
echo.
echo if your score is 3 = 100 points
echo if your score is 2 = 66 points
echo if your score is 1 = 33 points
echo if your score is 0 = 0 points
echo.
echo.
pause


exit
