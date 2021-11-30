#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <utils.h>

bool save_file_as_lines(const char* filename, char** lines, int rows, int cols){
    std::cout << "Saving map to \'" << filename << "\'...\n";
    std::fstream newfile;
    newfile.open(filename,std::ios::out);
    if(!newfile.is_open()){
        /* Create a blank file */
        std::ofstream outfile (filename);
        outfile << "" << std::endl;
        outfile.close();
    }
    newfile.close();

    newfile.open(filename,std::ios::out);  // open a file to perform write operation using file object
    if(newfile.is_open()){
        for(int r = 0; r<rows; r++){
            Calculate_Percentage(r,1);
            // std::cout << lines[r] << "\n";
            newfile << lines[r] << "\n";
        }
        newfile << "\n";
        newfile.close();
        std::cout << "Map successfully saved!\n";
        return true;
    }
    std::cout << "Error during saving!\n";
    return false;
}

bool load_file_as_lines(const char* filename, char** lines, int* rows, int* cols){
    std::fstream newfile;
    newfile.open(filename,std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){   //checking whether the file is open
        std::string tp;
        int ri = 0;
        int ci = 0;
        while(std::getline(newfile, tp)){ //read data from file object and put it into string.
            strcpy(lines[ri],tp.c_str());
            int len_of_line = strlen(lines[ri]);
            if(len_of_line > ci) ci = len_of_line;
            // std::cout << lines[ri] << "\n"; //print the data of the string
            ri++;
        }
        newfile.close(); //close the file object.
        *rows = ri;
        *cols = ci;
        return true;
    }
    return false;
}

bool is_odd(int n){
    return (n & 0x01);
}

bool is_even(int n){
    return !is_odd(n);
}

void snap_grid(int r, int c, int s, int* x, int* y){
    *x = c*s;
    *y = c*s/2 + r*s;
}

void snap_grid2(int r, int c, int s, int* x, int* y){
    bool row_is_even = is_even(r);
    
    if(row_is_even){
        *x = 2*c*s;
        *y = r*s/2;
    }
    else{
        *x = 2*c*s + s;
        *y = r*s/2;
    }
}

void snap_grid_with_zoom(int x1, int y1, int r, int c, int zoom, int* x, int* y){
    bool row_is_even = is_even(r);
    
    if(row_is_even){
        *x = x1 + 2*c*(8*zoom);
        *y = y1 + r*(8*zoom)/2;
    }
    else{
        *x = x1 + 2*c*(8*zoom) + (8*zoom);
        *y = y1 + r*(8*zoom)/2;
    }   
}

void snap_grid_with_zoom(int r, int c, int zoom, int* x, int *y){
    snap_grid_with_zoom(0,0,r,c,zoom,x,y);
}