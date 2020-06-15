__kernel void add(ulong n, global const double *a, double *b) {
    size_t i = get_global_id(0);
    b[i] = a[i] + 1;
}