__kernel void add(ulong n, global const double *a, global double *b) {
    size_t i = get_global_id(0);
    if(i < n) {
        b[i] = a[i] + 1;
    }
}