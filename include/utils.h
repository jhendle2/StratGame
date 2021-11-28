#pragma once

bool load_file_as_lines(const char* filename, char** lines, int* rows, int* cols);

bool is_even(int n);
bool is_odd(int n);

void snap_grid(int r, int c, int s, int* x, int* y);

void snap_grid2(int r, int c, int s, int* x, int* y);