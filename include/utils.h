#pragma once

#define Calculate_Percentage(r,c)   int percentage = (int) ( (double)(r) / (double)(rows) * 100.0 );\
                                    static int last_percentage = 0;\
                                    if(percentage > (last_percentage + 10)) {std::cout << percentage << "%\n";\
                                    last_percentage = percentage;}

bool save_file_as_lines(const char* filename, char** lines, int rows, int cols);
bool load_file_as_lines(const char* filename, char** lines, int* rows, int* cols);

bool is_even(int n);
bool is_odd(int n);

void snap_grid(int r, int c, int s, int* x, int* y);

void snap_grid2(int r, int c, int s, int* x, int* y);
void snap_grid_with_zoom(int x1, int y1, int r, int c, int zoom, int* x, int* y);
void snap_grid_with_zoom(int r, int c, int zoom, int* x, int* y);