/* Adam Haugen 180378 assignment 1 submission for Computer Organization */

/* This program reads a 2D image from an input file, applies
to it some image processing transformation upon request and
prints the output both to the screen and to a file.
The 2D image is stored and handled as a 2D array of characters. */

#include <stdio.h> /* include needed libraries */
#include <string.h>
#define MAXROW 50 /*set maximum sizes for image 2D array */
#define MAXCOL 50
#define AP '&' /*char symbols used in array */
#define PL '+'

/* global variables*/
FILE *fpin1, *fpout1; /*pointers to files*/

/*************************************************************/

/* This procedure prints a 2D char array row by row both to the screen and to an output file (global) */
void PrImage(char Image[MAXROW][MAXCOL], int Nrows, int Ncols)
{
    for (int i = 0; i < Nrows; i++)
    {
        for (int j = 0; j < Ncols; j++)
        {
            fprintf(stdout, "%c", Image[i][j]);
            fprintf(fpout1, "%c", Image[i][j]);
        }
        fprintf(stdout, "\n");
        fprintf(fpout1, "\n");
    }
}

/* Copy Coli of Mat1 to Colj of Mat2 of the same dimensions */
void CopyCol(char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
             int Nrows, int Coli, int Colj)
{

    for (int i = 0; i < Nrows; i++)
    {
        Mat2[i][Colj] = Mat1[i][Coli];
    }
}

/* Copy row i of Mat1 to row j of Mat2 of the same dimensions */
void CopyRow(char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
             int Ncols, int Rowi, int Rowj)
{

    for (int i = 0; i < Ncols; i++)
    {
        Mat2[Rowj][i] = Mat1[Rowi][i];
    }
}

/* Copy col i of Mat1 to row j of Mat2 */
void CopyColRow(char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
                int Nrows, int Ncols, int Coli, int Rowj)
{

    for (int i = 0; i < Nrows; i++)
    {
        Mat2[Rowj][i] = Mat1[i][Coli];
    }
}

/* Copy col i from (Nrows to 0) of Mat1 to row j of Mat2 from 0 to Ncols */
/* that is, copy the column, from bottom to top element,to the row */
/* 	copy column (Ncols-1) from (Nrows-1 element) to row (0) from (0) element
    copy column (Ncols-2) from (Nrows-1 element) to row (1) from (0) element
    copy column (0) from (Nrows-1 element) to row (Ncols-1) from (0) element*/
void CopyColrevRow(char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
                   int Nrows, int Ncols, int Coli, int Rowj)
{
    for (int i = 0; i < Nrows; i++)
    {
        Mat2[Rowj][i] = Mat1[Nrows - i - 1][Coli];
    }
}

/* Given the 2D char array of Image1 and its dimensions,
    construct the vertical mirror image in Image 2 as in:
    copy columns (0,1,...,Ncols-1) of Image1 to
    columns (Ncols-1, Ncols-2, ..., 1, 0) respectively of Image2 */
void VMirror(char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
             int Nrows, int Ncols)
{

    for (int i = 0; i < Nrows; i++)
    {
        CopyCol(Image1, Image2, Nrows, i, Ncols - i - 1);
    }
}

/* Given the 2D char array of Image1 and its dimensions,
    construct the horizontal mirror image in Image 2 as in:
        copy rows (0,1,...,Nrows-1) of Image1
        to rows (Nrows-1,Nrows-2,...,1,0) respectively of Image2 */
void HMirror(char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
             int Nrows, int Ncols)
{

    for (int i = 0; i < Nrows; i++)
    {
        CopyRow(Image1, Image2, Ncols, i, Nrows - i - 1);
    }
}

/*Given the 2D char array of Image1 and its dimensions,
    construct the flipped image in Image2 along the top
    left to bottom right diagonal as in:
         copy col 0 of Image1 -> row 0 of Image2
         copy col 1 of Image1 -> row 1 of Image2
        ......................................
         copy col (Ncols-1) of Image1 to row (Ncols-1) of Image2
         NOTE: sizes of Image2 are inverted from Image1 */
void DiagR(char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
           int Nrows, int Ncols)
{
    for (int i = 0; i < Nrows; i++)
    {
        CopyColRow(Image1, Image2, Nrows, Ncols, i, i);
    }
}

/*Given the 2D char array of Image1 and its dimensions,
    construct the flipped image in Image2 along the top
    right to bottom left diagonal as in:
        copy col (Ncols-1) of Image1 -> row 0 of Image2
        copy col (Ncols-2) of Image1 -> row 1 of Image2
        ......................................
        copy col 0 of Image1 -> row (Ncols-1) of Image2
        NOTE: sizes of Image2 are inverted from Image1 */
void DiagL(char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
           int Nrows, int Ncols)
{

    for (int i = 0; i < Nrows; i++)
    {
        CopyColrevRow(Image1, Image2, Nrows, Ncols, Ncols - i - 1, i);
    }
}

/*Given the 2D char array of Image1 and its dimensions,
    construct the rotated by 90 degree image in Image2 */
void RotR(char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
          int Nrows, int Ncols)
{

    for (int i = 0; i < Ncols; i++)
    {
        CopyColrevRow(Image1, Image2, Nrows, Ncols, i, i);
    }
}

/*Read from an input file two integers for the number of rows and
    number of columns of the image to be processed*/
void RdSize(int *Nrows, int *Ncols)
{
    fscanf(fpin1, "%d", Nrows);
    fscanf(fpin1, "%d", Ncols);
    fprintf(stdout, "Nrows = %d, Ncols = %d\n", *Nrows, *Ncols);
    fprintf(fpout1, "Nrows = %d, Ncols = %d\n", *Nrows, *Ncols);
}

/*Read from an input file the integers describing the image to
    be processed and store the corresponding character in the 2D array*/
void RdImage(char Image1[MAXROW][MAXCOL], int Nrows, int Ncols)
{
    int compareVal; // compareVal is used to compare the string read from the file
    for (int i = 0; i < Nrows; i++)
    {
        for (int j = 0; j < Ncols; j++)
        {
            compareVal = -99; // initialize compareVal to a value that will not be returned by strcmp
            fscanf(fpin1, "%s", &Image1[i][j]);
            compareVal = strcmp(&Image1[i][j], "0");
            if (compareVal == 0) // 0's are pluses, all other numbers are ampersands
            {
                Image1[i][j] = PL;
            }
            else
            {
                Image1[i][j] = AP;
            }
        }
    }
}

/*Read integers from an opened input file until EOF, and call
the appropriate stub routine for each task represented*/
int RdDoTask(char Image1[MAXROW][MAXCOL],
             char Image2[MAXROW][MAXCOL], int Nrows, int Ncols)
{
    int task;
    int eof;

    while (1)
    {
        eof = fscanf(fpin1, "%d", &task); // fscanf returns EOF when it reaches the end of the file
        if (eof == EOF)
            break;
        switch (task)
        {
        case 1:
            VMirror(Image1, Image2, Nrows, Ncols);
            break;
        case 2:
            HMirror(Image1, Image2, Nrows, Ncols);
            break;
        case 3:
            DiagR(Image1, Image2, Nrows, Ncols);
            break;
        case 4:
            DiagL(Image1, Image2, Nrows, Ncols);
            break;
        case 5:
            RotR(Image1, Image2, Nrows, Ncols);
            break;
        default:
            fprintf(stdout, "Invalid task number %d\n", task);
            fprintf(fpout1, "Invalid task number %d\n", task);
        }
        fprintf(stdout, "Task %d completed \n", task);
        fprintf(fpout1, "Task %d completed \n", task);
        if (task <= 2) // rows and columns flip for tasks 3 - 5
        {
            PrImage(Image2, Nrows, Ncols);
            // formatting for output
            fprintf(stdout, "\n");
            fprintf(fpout1, "\n");
        }
        else
        {
            PrImage(Image2, Ncols, Nrows);
            // formatting for output
            fprintf(stdout, "\n");
            fprintf(fpout1, "\n");
        }
    }
    return (0);
}

/*************************************************************/
int main()
{

    int eof;

    /* real declarations you will need */
    int Rsize1, Csize1;          // image sizes
    char IMchr1[MAXROW][MAXCOL]; // original image
    char IMchr2[MAXROW][MAXCOL]; // resulting image after processing

    fprintf(stdout, "Hello:\n"); /*start of program*/

    /*open all input and output files*/
    fpin1 = fopen("A1InF.txt", "r"); /* open the file for reading */
    if (fpin1 == NULL)
    {
        fprintf(stdout, "Cannot open input file - Bye\n");
        return (0); /*if problem, exit program*/
    }

    fpout1 = fopen("A1OutF.txt", "w"); /* open the file for writing */
    if (fpout1 == NULL)
    {
        fprintf(stdout, "Cannot open output file - Bye\n");
        return (0); /*if problem, exit program*/
    }

    /*hello message to screen and output file*/
    fprintf(stdout, "\n Captain Picard - Student Number V00123456 \n");
    fprintf(stdout, "\n File = 367Assign1.c	- Fall 2024 \n");
    fprintf(stdout, "\n Welcome to Computer Organization, Assignment 1 \n\n");
    fprintf(fpout1, "\n Captain Picard - Student Number V00123456 \n");
    fprintf(fpout1, "\n File = 367Assign1.c	- Fall 2024 \n");
    fprintf(fpout1, "\n Welcome to Computer Organization, Assignment 1 \n\n");

    fprintf(stdout, "Starting: \n");
    fprintf(fpout1, "Starting: \n");

    /*Read in the sizes for the image*/
    /* call RdSize */
    RdSize(&Rsize1, &Csize1);
    /*Read in the image*/
    /* call RdImage */
    RdImage(IMchr1, Rsize1, Csize1);

    /*Print the initial image*/
    fprintf(stdout, "Initial IMchr1 contains: \n");
    fprintf(fpout1, "Initial IMchr1 contains: \n");
    /* call PrImage */
    PrImage(IMchr1, Rsize1, Csize1);
    // formatting for output
    fprintf(stdout, "\n");
    fprintf(fpout1, "\n");
    /* read all integers from file until EOF - for each call the
    required stub routine for the image processing task*/
    /* call RdDoTask */
    eof = RdDoTask(IMchr1, IMchr2, Rsize1, Csize1);

    /* Closure */
    fprintf(stdout, "The program is all done - Bye! \n");
    fprintf(fpout1, "The program is all done - Bye! \n");

    fclose(fpin1); /* close the files */
    fclose(fpout1);

    return (0);
}
